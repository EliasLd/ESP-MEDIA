#include "draw.h"

#define COLOR_X 60
#define COLOR_Y 20
#define COLOR_W 15
#define COLOR_H 10

#define COLOR_GAP_X 10

uint16_t colors[] = {TFT_WHITE, TFT_BLACK, TFT_BLUE, TFT_RED,
                        TFT_YELLOW, TFT_ORANGE, TFT_PURPLE, TFT_GREEN};
TFT_eSPI_Button cinputs[8];          

uint16_t color = TFT_WHITE;

void initDraw(TFT_eSPI tft){
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(0, 40, SCREEN_WIDTH, SCREEN_HEIGHT - 30, TFT_DARKGREY);
}

void printDrawingButton(TFT_eSPI tft, TFT_eSPI_Button erase[1]){
    erase[0].initButton(&tft, SCREEN_WIDTH - 20, 20, 30, 20, TFT_RED, TFT_BLACK, TFT_WHITE, (char*)"-", 1);
    erase[0].drawButton();
    u_int16_t outline;
    for(int i = 0 ; i < 8 ; i++)
    {
        if(colors[i] == TFT_BLACK) {outline = TFT_WHITE;}
        else {outline = colors[i];}
        cinputs[i].initButton(&tft, COLOR_X + i * (COLOR_W/2 + COLOR_GAP_X)
                            , COLOR_Y, COLOR_W, COLOR_H, outline, colors[i]
                            , colors[i], (char*)" ", 1);
        cinputs[i].drawButton();
    }
}

void drawing(TFT_eSPI tft, TFT_eSPI_Button erase[1]){
    uint16_t x = 0, y = 0;
    for (int i = 0; i < 8; i++) {
        if (tft.getTouch(&x, &y) && x < SCREEN_WIDTH && x > 0 && y > 40 && y < SCREEN_HEIGHT) {
            tft.fillCircle(x, y, 5, color);
        }
        if (pressed(tft, erase[0])) {
            erase[0].drawButton(false);
            tft.fillRect(0, 40, SCREEN_WIDTH, SCREEN_HEIGHT - 30, TFT_DARKGREY);
        }
        if (pressed(tft, cinputs[i])) {
            color = colors[i];
        }
    }
}