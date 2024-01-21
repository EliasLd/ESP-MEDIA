#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "boot.h"
#include "logo.h"
#include "menu.h"

TFT_eSPI tfts = TFT_eSPI();
TFT_eSPI_Button inputs[3];
TFT_eSPI_Button back[1];
const char *inputsLabel[] = {"Games", "Draw", "Netwrk"};
int degree = 0;

void setup() {
  Serial.begin(9600);
  tfts.init();
  tfts.setRotation(1);
  tfts.fillScreen(TFT_WHITE);
  bootAnimation(tfts);
  tfts.drawBitmap(SCREEN_WIDTH/3 - 20, 20, logo,  150, 150, TFT_WHITE);
  delay(500);
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
          if(Backed(tfts, back)) {degree--;}
        }
      }
    }
  }
}

