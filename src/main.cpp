#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "boot.h"
#include "logo.h"

TFT_eSPI tfts = TFT_eSPI();

void setup() {
  Serial.begin(9600);
  tfts.init();
  tfts.setRotation(1);
  tfts.fillScreen(TFT_WHITE);
  bootAnimation(tfts);
  tfts.drawBitmap(SCREEN_WIDTH/3 - 20, 20, logo,  150, 150, TFT_WHITE);
  delay(500);
  chargement(tfts, TFT_BLACK);
  tfts.fillScreen(TFT_BLACK);
}

void loop() {
  
}

