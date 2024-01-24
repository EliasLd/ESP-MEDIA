#define BOOT_H

#define SCREEN_HEIGHT 320
#define SCREEN_WIDTH 240

void bootAnimation(TFT_eSPI tft);
void textAnimation(TFT_eSPI tft, const char* text, uint16_t color, int size);
void chargement(TFT_eSPI tft, uint32_t color);