/*
  Pipeline status

  RGB LED status monitor for pipelines and other application
  Uses MQTT and JSON to comunicate.

  Created 11th of July 2019
  By André Lademann <vergissberlin@gmail.com>

  https://github.com/vergissberlin/esp8266-mqtt-led
  https://github.com/kitesurfer1404/WS2812FX
*/

#include <WS2812FX.h>

#define LED_PIN    4  // digital pin used to drive the LED strip
#define LED_COUNT 15  // number of LEDs on the strip

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setupLed() {
  ws2812fx.init();
  ws2812fx.setBrightness(255);
  ws2812fx.setSegment(0, 0, 0, FX_MODE_STATIC, BLUE, 1500, false);
  ws2812fx.start();
}

void readConfig() {
  // JSON parser
  JsonObject obj = doc.as<JsonObject>();

  // IF (doc object is not empty)
  if (doc.isNull() == false) {

    String method = obj["method"];
    Serial.print("\tmethod:\t\t");
    Serial.println(method);

    uint16_t position = obj["position"];
    Serial.print("\tposition:\t\t");
    Serial.println(position);


    // Set colours
    uint8_t r = obj["color"]["r"];
    uint8_t g = obj["color"]["g"];
    uint8_t b = obj["color"]["b"];
    Serial.print("\trgb:\t\t");
    Serial.print(r);
    Serial.print(", ");
    Serial.print(g);
    Serial.print(", ");
    Serial.println(b);

    // Cast rgb in hex in uint32_t
    uint32_t colour = ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
    //uint32_t colors[] = {RED, BLUE};

    // Set pixel effect
    ws2812fx.setSegment(position, position, position, FX_MODE_STATIC, colour, 1500, false);

    // Clear the document
    doc.clear();
  }
}

void loopLed() {
  ws2812fx.service();
  readConfig();
}
