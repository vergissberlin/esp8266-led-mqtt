/*
  Pipeline status

  RGB LED status monitor for pipelines and other application
  Uses MQTT and JSON to comunicate.

  Created 11th of July 2019
  By André Lademann <vergissberlin@gmail.com>

  https://github.com/vergissberlin/esp8266-mqtt-led
*/
#include <TimedBlink.h>

TimedBlink status(pinLedStatus);

void setupBlink() {
  pinMode(pinLedStatus, OUTPUT);
}

void loopBlink() {
  status.blink();
}
