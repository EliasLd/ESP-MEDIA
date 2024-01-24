#define SCREEN_HEIGHT 320
#define SCREEN_WIDTH 240

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "./menu/menu.h"

void initDraw(TFT_eSPI tft);
void printEraseButton(TFT_eSPI tft, TFT_eSPI_Button erase[1]);
void drawing(TFT_eSPI tft, TFT_eSPI_Button erase[1]);