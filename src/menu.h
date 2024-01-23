#include "Free_Fonts.h"

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <FS.h>
#include <TFT_eWidget.h>

#define SCREEN_HEIGHT 320
#define SCREEN_WIDTH 240

#define INPUT_W 68
#define INPUT_H 30
#define INPUT_GAP_X 5
#define INPUT_GAP_Y 20 

#define BACK_W 30
#define BACK_H 20
#define BACK_X 20
#define BACK_Y 20

#define CALIBRATION_FILE "/TouchCalData1"
#define REPEAT_CAL false

void printMenu(TFT_eSPI tft, TFT_eSPI_Button inputs[3], const char *inputsLabel[]);
bool menuInput(TFT_eSPI tft, TFT_eSPI_Button inputs[3], const char *inputsLabel[]);
void printBackButton(TFT_eSPI tft, TFT_eSPI_Button back[1]);
bool Backed(TFT_eSPI tft, TFT_eSPI_Button back[1]);

void printMenu(TFT_eSPI tft, TFT_eSPI_Button inputs[3], const char *inputsLabel[]){
    tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(FMO9);

    const char *str = "MENU";

    int sstr = tft.textWidth(str, 4);
    int xstr = SCREEN_WIDTH/2 - sstr / 2;

    tft.drawString(str, xstr, 20, 4);

    for(uint8_t i = 0 ; i < 3 ; i++){
        inputs[i].initButton(&tft, 45  + i * (INPUT_W + INPUT_GAP_X), 80,
                            INPUT_W, INPUT_H, TFT_DARKGREY, TFT_DARKGREY, TFT_WHITE,
                            (char*)inputsLabel[i], 1);
        inputs[i].drawButton();
    }
}

bool menuInput(TFT_eSPI tft, TFT_eSPI_Button inputs[3], const char *inputsLabel[]){
    uint16_t tx = 0, ty = 0;
    bool pressed = false;
    bool t;
    
    for(int i = 0 ;  i < 3 ; i++){
       t = tft.getTouch(&tx, &ty);
       if(inputs[i].contains(tx, ty)){
          inputs[i].drawButton(true);
          inputs[i].press(true);
          pressed = true;
          delay(100);
       }
    }
    return pressed;
}

void printBackButton(TFT_eSPI tft, TFT_eSPI_Button back[1]){
  back[0].initButton(&tft, BACK_X, BACK_Y, BACK_W, BACK_H, 
                  TFT_RED, TFT_RED, TFT_WHITE,
                  (char*)"<-", 1);
  back[0].drawButton();
}

bool Backed(TFT_eSPI tft, TFT_eSPI_Button back[1]){
  uint16_t bx = 0, by = 0;
  bool pressed = false;
  bool b;

  b = tft.getTouch(&bx, &by);
  if(back[0].contains(bx, by)){
    back[0].drawButton(true);
    pressed = true;
    delay(50);
  }
  return pressed;
}
