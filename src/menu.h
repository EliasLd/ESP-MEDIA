#include "Free_Fonts.h"

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define INPUT_W 68
#define INPUT_H 30
#define INPUT_GAP_X 35
#define INPUT_GAP_Y 20 

#define BACK_W 30
#define BACK_H 20
#define BACK_X 10
#define BACK_Y SCREEN_HEIGHT - 10 - BACK_H

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
        inputs[i].initButton(&tft, 60 + i * (INPUT_W + INPUT_GAP_X), 80,
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
       if(inputs[i].contains(tx, ty - 70)){
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
  if(back[0].contains(bx, by + 183)){
    back[0].drawButton(true);
    pressed = true;
    delay(50);
  }
  return pressed;
}

void touchCalibrate(TFT_eSPI tft)
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // Calibrate
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(20, 0);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.println("Touch corners as indicated");

  tft.setTextFont(1);
  tft.println();

  tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

  Serial.println(); Serial.println();
  Serial.println("// Use this calibration code in setup():");
  Serial.print("  uint16_t calData[5] = ");
  Serial.print("{ ");

  for (uint8_t i = 0; i < 5; i++)
  {
    Serial.print(calData[i]);
    if (i < 4) Serial.print(", ");
  }

  Serial.println(" };");
  Serial.print("  tft.setTouch(calData);");
  Serial.println(); Serial.println();

  tft.fillScreen(TFT_BLACK);
  
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println("Calibration complete!");
  tft.println("Calibration code sent to Serial port.");

  delay(4000);
}