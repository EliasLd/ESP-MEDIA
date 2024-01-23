#define SCREEN_HEIGHT 320
#define SCREEN_WIDTH 240

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

void initDraw(TFT_eSPI tft);
void printEraseButton(TFT_eSPI tft, TFT_eSPI_Button erase[1]);
bool Erased(TFT_eSPI tft, TFT_eSPI_Button erase[1]);
void drawing(TFT_eSPI tft, TFT_eSPI_Button erase[1]);

void initDraw(TFT_eSPI tft){
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(0, 40, SCREEN_WIDTH, SCREEN_HEIGHT - 30, TFT_DARKGREY);
}

void printEraseButton(TFT_eSPI tft, TFT_eSPI_Button erase[1]){
    erase[0].initButton(&tft, SCREEN_WIDTH - 20, 20, 30, 20, TFT_RED, TFT_BLACK, TFT_WHITE, (char*)"-", 1);
    erase[0].drawButton();
}

bool Erased(TFT_eSPI tft, TFT_eSPI_Button erase[1]){
    uint16_t x = 0, y = 0;
    bool pressed = false;
    if(tft.getTouch(&x, &y) && erase[0].contains(x, y)){
        erase[0].drawButton(true);
        pressed = true;
        delay(50);
    }
    return pressed;
}

void drawing(TFT_eSPI tft, TFT_eSPI_Button erase[1]){
    uint16_t x = 0, y = 0;
    if(tft.getTouch(&x, &y) && x < SCREEN_WIDTH && x > 0 && y > 40 && y < SCREEN_HEIGHT){
       tft.fillCircle(x, y, 5, TFT_YELLOW);
       delay(1);
    }
    if(Erased(tft, erase)){
        erase[0].drawButton(false);
        tft.fillRect(0, 40, SCREEN_WIDTH, SCREEN_HEIGHT - 30, TFT_DARKGREY);
    }
}