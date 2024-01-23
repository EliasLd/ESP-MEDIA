#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "boot.h"
#include "logo.h"
#include "menu.h"
#include "draw.h"

TFT_eSPI tfts = TFT_eSPI();
TFT_eSPI_Button inputs[3];
TFT_eSPI_Button back[1];
TFT_eSPI_Button erase[1];
const char *inputsLabel[] = {"Games", "Draw", "Netwrk"};
int degree = 0;
uint16_t calData[5] = {342, 3174, 533, 3248, 4};

void setup() {
  Serial.begin(9600);
  tfts.init();
  tfts.setRotation(0);
  tfts.fillScreen(TFT_WHITE);
  tfts.setTouch(calData);

  bootAnimation(tfts);
  tfts.drawBitmap(SCREEN_WIDTH/4 - 17, 50, logo,  150, 150, TFT_WHITE);
  delay(3000);

  chargement(tfts, TFT_BLACK);
  tfts.fillScreen(TFT_BLACK);
}

void loop() {
  printMenu(tfts, inputs, inputsLabel);
  while(!menuInput(tfts, inputs, inputsLabel) && degree == 0){ }
  for(int i = 0 ; i < 3 ; i ++){
    if(inputs[i].isPressed()){

      if(inputsLabel[i] == "Games"){
        degree++;
        tfts.fillScreen(TFT_BLACK);
        printBackButton(tfts, back);
        while(degree == 1){
          if(Backed(tfts, back)) {degree--; inputs[i].press(false);}
        }
      }

      if(inputsLabel[i] == "Draw"){
        degree++;
        initDraw(tfts);
        printBackButton(tfts, back);
        printEraseButton(tfts, erase);
        while(degree == 1){
          drawing(tfts, erase);
          if(Backed(tfts, back)) {degree--; inputs[i].press(false);}

        }
      }
      
    }
  }
}

