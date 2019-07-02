/*
  Pipeline monitor
  
  RGB LED status monitor for pipelines and other application
  Uses MQTT and JSON to comunicate.
  
  The circuit:
  * 10K resistor attached to pin 2 from ground 
  * Output: External LED to visualize the fill status on pin XX
  * Output: Internal LED to visualize the maintance status on pin XX
  * Output: Internal LED to visualize the wifi status on pin XX
  * list the components attached to each input
  * list the components attached to each output 

  Created 11th of July 2019
  By André Lademann <vergissberlin@gmail.com>
  https://github.com/vergissberlin/esp8266-mqtt-led
  
  @example
  {
    "method": "color",
    "position": 0,
    "color": {
      "r": 150,
      "b": 255,
      "g": 75
    }
  }

  @example
  {
    "method": "status",
    "position": 0,
    "status": "paused"
  }

  Available methods:
  - fade
  - blink
  - color
  - status

  Available status:
  - succeed (green)
  - failed (red)
  - in progress (yellow blinking)
  - paused (blue)
*/

// Libraries
//#include <ArduinoJson.h>

// Load configuration
#include "config.h"

// Include libraries
#include "blink.h"
#include "mqtt.h"
#include "pins.h"
#include "wifi.h"
#include "led.h"
#include "ota.h"

// Data storage
//StaticJsonDocument<512> doc

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println(F("\n      ✰✰✰  Pipeline monitor booting ✰✰✰      "));
  Serial.print("Device id: ");
  Serial.println(String(deviceId));
  Serial.println("\n\
       _            _ _                                    _ _\n\
 _ __ (_)_ __   ___| (_)_ __   ___   _ __ ___   ___  _ __ (_) |_ ___  _ __\n\
| '_ \| | '_ \ / _ \ | | '_ \ / _ \ | '_ ` _ \ / _ \| '_ \| | __/ _ \| '__|\n\
| |_) | | |_) |  __/ | | | | |  __/ | | | | | | (_) | | | | | || (_) | |\n\
| .__/|_| .__/ \___|_|_|_| |_|\___| |_| |_| |_|\___/|_| |_|_|\__\___/|_|\n\
|_|     |_|\n\
  ");
  
  setupPins();
  setupWifi(String(deviceId));
  setupOta();
  setupMqtt(deviceId);
  setupLed();

  //doc["data"] = "dirk";
  //char payload[512];
  //serializeJson(doc, payload);
}

void loop() {
  loopMqtt();
  loopOta();
  loopPin();
  loopLed();
}