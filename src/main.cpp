#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "boot.h"

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(9600);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_WHITE);
  boot_animation(tft);
}

void loop() {
  
}

