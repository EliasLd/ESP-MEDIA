#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "boot/boot.h"
#include "logo/logo.h"
#include "menu/menu.h"
#include "draw/draw.h"
#include "games/pong.h"

TFT_eSPI tfts = TFT_eSPI();
TFT_eSPI_Button inputs[3];
TFT_eSPI_Button gamesInput[3];
TFT_eSPI_Button back[1];
TFT_eSPI_Button erase[1];

const char *inputsLabel[] = {"Games", "Draw", "Netwrk"};
const char *gamesLabel[] = {"Pong", "Mine", "Jump"};
int degree = 0;
uint16_t calData[5] = {342, 3174, 533, 3248, 4};  // touch calibration

Racket racket(40, 4, 0, SCREEN_HEIGHT - SCREEN_HEIGHT/4);
Ball ball(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 5, true, false, true, false, 3);

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
  printMenu(tfts, inputs, inputsLabel, "APPLICATIONS");
  while(!menuInput(tfts, inputs, inputsLabel) && degree == 0){ }
  for(int i = 0 ; i < 3 ; i ++){
    if(inputs[i].isPressed()){

      if(inputsLabel[i] == "Games"){
        degree++;
        tfts.fillScreen(TFT_BLACK);
        printMenu(tfts, gamesInput, gamesLabel, "GAMES");
        printBackButton(tfts, back);
        while(degree == 1){
          if(pressed(tfts, back[0])) {tfts.fillScreen(TFT_BLACK); degree--; inputs[i].press(false);}
          if(menuInput(tfts, gamesInput, gamesLabel)){
            for(int j = 0 ; j < 3 ; j++){
                if(gamesInput[i].isPressed()){
                  if(gamesLabel[i] = "Pong"){
                    tfts.fillScreen(TFT_PURPLE);
                    printRacket(tfts, &racket, TFT_WHITE);
                    while(true){
                      moveRacket(tfts, &racket);
                      updateBall(tfts, &ball, &racket);
                      printBall(tfts, &ball, TFT_WHITE);
                      physic(tfts, &ball, &racket);
                    }
                }
              }
            }
          }
        }
      }
     
      if(inputsLabel[i] == "Draw"){
        degree++;
        initDraw(tfts);
        printBackButton(tfts, back);
        printDrawingButton(tfts, erase);
        while(degree == 1){
          drawing(tfts, erase);
          if(pressed(tfts, back[0])) {tfts.fillScreen(TFT_BLACK); degree--; inputs[i].press(false);}
        }
      }
      
    }
  }
}

