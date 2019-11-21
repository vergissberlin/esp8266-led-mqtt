/*
  Pipeline status

  RGB LED status monitor for pipelines and other application
  Uses MQTT and JSON to comunicate.

  Created 11th of July 2019
  By André Lademann <vergissberlin@gmail.com>

  https://github.com/vergissberlin/esp8266-mqtt-led
  https://pubsubclient.knolleary.net/api.html#connect4

*/
#include <PubSubClient.h>
#include <WiFiClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

char mqttFeedWithId[200];


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Message arrived:");
  Serial.print("\tjson string:\t");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println("");

  // JSON parser
  deserializeJson(doc, payload, length);
  JsonObject obj = doc.as<JsonObject>();

}


void connect() {
  Serial.println(F("\n▶ MQTT"));

  // Device id
  char deviceIdChar[8];
  sprintf(deviceIdChar, "%lu", deviceId);

  // Feeds generation
  snprintf(mqttFeedWithId, sizeof(mqttFeedWithId), mqttFeed, deviceIdChar);

  // Connecting
  Serial.print(F("Connecting to \""));
  Serial.print(mqttServer);
  Serial.print(F("\"\t"));
  while (!client.connected()) {
    if (client.connect(deviceIdChar, mqttUsername, mqttPassword, mqttWillTopic, mqttQos, mqttRetain, deviceIdChar)) {
      Serial.print("\nStatus:\t\tMQTT connected. State ");
      Serial.println(client.state());
      Serial.print("Feed:\t\t");
      Serial.println(mqttFeedWithId);
      client.subscribe(mqttFeedWithId);
    } else {
      Serial.print(F("☉"));
      delay(1000);
    }
  }
}


void setupMqtt(const uint32_t deviceId) {
  // Connection
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

void loopMqtt() {
  if (!client.connected()) {
    connect();
  }
  client.loop();
}


/**
   @see https://arduinojson.org/v6/faq/how-to-use-arduinojson-with-pubsubclient/
*/
void mqttPublish(char* value) {
  if (! client.publish(mqttFeedWithId, value)) {
    status.blink(1000, 50);
  } else {
    Serial.println("Data:\t\t" + String(value));
    status.blinkOff();
  }
}
