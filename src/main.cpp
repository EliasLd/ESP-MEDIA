#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "boot.h"

TFT_eSPI tfts = TFT_eSPI();

void setup() {
  Serial.begin(9600);
  tfts.init();
  tfts.setRotation(1);
  tfts.fillScreen(TFT_WHITE);
  bootAnimation(tfts);
}

void loop() {
  
}

