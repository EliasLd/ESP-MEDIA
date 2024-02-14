#include "pong.h"

#define SCREEN_HEIGHT 320
#define SCREEN_WIDTH 240

Racket racket(50, 4, 0, SCREEN_HEIGHT - SCREEN_HEIGHT/3);

void printRacket(TFT_eSPI tft, Racket *R){
    tft.fillRect(R->x, R->y, R->w, R->h, TFT_WHITE);
}

