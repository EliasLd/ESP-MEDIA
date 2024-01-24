#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

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

void printMenu(TFT_eSPI tft, TFT_eSPI_Button inputs[3], const char *inputsLabel[]);
bool menuInput(TFT_eSPI tft, TFT_eSPI_Button inputs[3], const char *inputsLabel[]);
void printBackButton(TFT_eSPI tft, TFT_eSPI_Button back[1]);
bool pressed(TFT_eSPI tft, TFT_eSPI_Button button);


