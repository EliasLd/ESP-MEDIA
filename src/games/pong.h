#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#define SCREEN_HEIGHT 320
#define SCREEN_WIDTH 240

class Racket {
    public:
        int w, h;
        int x, y;
        
        Racket(int w, int h, int x, int y){
            this->w = w;
            this->h = h;
            this->x = x;
            this->y = y;
        }
};

class Block {
    public:
        int w, h;
        int x, y;
        bool destroyed;

        Block(int w, int h, int x, int y, bool destroyed){
            this->w = w;
            this->h = h;
            this->x = x;
            this->y = y;
            this->destroyed = destroyed;
        } 
};

void printRacket(TFT_eSPI tft, Racket *R, uint16_t color);
void moveRacket(TFT_eSPI tft, Racket *R);