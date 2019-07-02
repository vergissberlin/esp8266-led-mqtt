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

// #include <ArduinoJson.h>

char mqttFeedWithId[200];

void setupMqtt(const uint32_t deviceId) {
  Serial.println(F("\n▶ MQTT"));
  char deviceIdChar[8];
  sprintf(deviceIdChar,"%lu", deviceId);

  // Connection
  client.setServer(mqttServer, mqttPort);
  client.connect(deviceIdChar, mqttUsername, mqttPassword, mqttWillTopic, mqttQos, mqttRetain, deviceIdChar);

  // Feeds generation
  snprintf(mqttFeedWithId, sizeof(mqttFeedWithId), mqttFeed, deviceIdChar);
  
  if(client.connected()) {
    Serial.print("MQTT connected:\t");
    Serial.println(client.state());
  } else {
    Serial.println("MQTT not connected");
  }
  client.loop();
}

void loopMqtt() {
}

/**
 * @see https://arduinojson.org/v6/faq/how-to-use-arduinojson-with-pubsubclient/
 */
void mqttPublish(char* value) {
  if (! client.publish(mqttFeedWithId, value)) {
    status.blink(1000,50);
  } else {
    Serial.println("Data:\t\t" + String(value));
    status.blinkOff();
  }
}

int replaceChar(char *str, char orig, char rep) {
    char *ix = str;
    int n = 0;
    while((ix = strchr(ix, orig)) != NULL) {
        *ix++ = rep;
        n++;
    }
    return n;
}
