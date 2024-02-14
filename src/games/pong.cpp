#include "pong.h"

#define SCREEN_HEIGHT 320
#define SCREEN_WIDTH 240

void printRacket(TFT_eSPI tft, Racket *R, uint16_t color){
    tft.fillRect(R->x, R->y, R->w, R->h, color);
}

void moveRacket(TFT_eSPI tft, Racket *R){
    u_int16_t tx = 0, ty = 0;
    bool pressed = false;

    if(tft.getTouch(&tx, &ty) && ty > R->y && (tx < R->x + R->w && tx > R->x - 10)){
        printRacket(tft, R, TFT_PURPLE);
        R->x = tx;
        printRacket(tft, R, TFT_WHITE);
    }
}

