/*
  Pipeline status

  RGB LED status monitor for pipelines and other application
  Uses MQTT and JSON to comunicate.

  Created 11th of July 2019
  By André Lademann <vergissberlin@gmail.com>

  https://github.com/vergissberlin/esp8266-mqtt-led
  https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use
*/

#include <Adafruit_NeoPixel.h>

#define PIN D2 // The pin where you connect the neopixel dataline
#define NUMPIXELS 16 // How many NeoPixels are attached

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setupLed() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loopLed() {
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) {
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels.setBrightness(64);
    pixels.show();   // Send the updated pixel colors to the hardware.
  }
}
