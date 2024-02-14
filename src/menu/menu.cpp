#include "menu.h"
#include "./fonts/Free_Fonts.h"

void printMenu(TFT_eSPI tft, TFT_eSPI_Button inputs[3], const char *inputsLabel[], const char* menuName){
    tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(FMO9);

    const char *str = menuName;

    int sstr = tft.textWidth(str, 4);
    int xstr = SCREEN_WIDTH/2 - sstr / 2;

    tft.drawString(str, xstr, 20, 4);

    for(uint8_t i = 0 ; i < 3 ; i++){
        inputs[i].initButton(&tft, 45  + i * (INPUT_W + INPUT_GAP_X), 80,
                            INPUT_W, INPUT_H, TFT_ORANGE, TFT_YELLOW, TFT_BLACK,
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

bool pressed(TFT_eSPI tft, TFT_eSPI_Button button){
  uint16_t x = 0, y = 0;
  bool pressed = false;
  if(tft.getTouch(&x, &y) && button.contains(x, y)){
    button.drawButton(true);
    pressed = true;
  }
  return pressed;
}