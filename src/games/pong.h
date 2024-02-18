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


        void printBlock(TFT_eSPI tft, u_int16_t color){
            tft.fillRect(this->x, this->y, this->w, this->h, color);
        } 
};

class Ball {
    public:
       int cx, cy;
       int r;
       bool right, left, up, down;
       int speed;

       Ball(int cx, int cy, int r, bool right, bool left, bool up, bool down, int speed){
           this->cx = cx;
           this->cy = cy;
           this->r = r;
           this->right = right;
           this->left = left;
           this->up = up;
           this->down = down;
           this->speed = speed;
       }
};

void printRacket(TFT_eSPI tft, Racket *R, uint16_t color);
void moveRacket(TFT_eSPI tft, Racket *R);
void printBall(TFT_eSPI tft, Ball *B, u_int16_t color);
void updateBall(TFT_eSPI tft, Ball *B, Racket *R);
bool physic(TFT_eSPI tft, Ball *B, Racket *R);