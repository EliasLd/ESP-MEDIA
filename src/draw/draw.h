#define SCREEN_HEIGHT 320
#define SCREEN_WIDTH 240

#define CINPUT_X 30
#define CINPUT_Y 20
#define CINPUT_W 10
#define CINPUT_H 10
#define CINPUT_GAP_X 5

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "./menu/menu.h"

void initDraw(TFT_eSPI tft);
void printEraseButton(TFT_eSPI tft, TFT_eSPI_Button erase[1]);
void drawing(TFT_eSPI tft, TFT_eSPI_Button erase[1]);