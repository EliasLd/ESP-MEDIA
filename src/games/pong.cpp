#include "pong.h"

#define SCREEN_HEIGHT 320
#define SCREEN_WIDTH 240

void printRacket(TFT_eSPI tft, Racket *R, uint16_t color){
    tft.fillRect(R->x, R->y, R->w, R->h, color);
}

void moveRacket(TFT_eSPI tft, Racket *R){
    u_int16_t tx = 0, ty = 0;
    bool pressed = false;

    if(tft.getTouch(&tx, &ty) && ty > R->y && (tx < R->x + R->w + 10 && tx > R->x - 10)){
        printRacket(tft, R, TFT_PURPLE);
        R->x = tx - R->w / 2;
        printRacket(tft, R, TFT_WHITE);
    }
}

void printBall(TFT_eSPI tft, Ball *B, uint16_t color){
    tft.fillCircle(B->cx, B->cy, B->r, color);
}

void updateBall(TFT_eSPI tft, Ball *B, Racket *R){
    printBall(tft, B, TFT_PURPLE);
    if(B->right) {B->cx += B->speed;}
    if(B->left) {B->cx -= B->speed;}
    if(B->up) {B->cy -= B->speed;}
    if(B->down) {B->cy += B->speed;}
}

bool physic(TFT_eSPI tft, Ball *B, Racket *R){
    if(B->cx + B->r >= SCREEN_WIDTH){
        B->left = true;
        B->right = false;
    }
    if(B->cx - B->r <= 0){
        B->right = true;
        B->left = false;
    }
    if(B->cy - B->r <= 0){
        B->down = true;
        B->up = false;
    }
    if((B->cy + B->r >= R->y - 1 && B->cy + B->r <= R->y + 1) && (B->cx <= R->x + R->w && B->cx >= R->x)){
        B->up = true;
        B->down = false;
    }
    if(B->cy >= SCREEN_HEIGHT){return true;}
    return false;
}