#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

void bootAnimation(TFT_eSPI tft);
void textAnimation(TFT_eSPI tft, const char* text, uint16_t color, int size);

void bootAnimation(TFT_eSPI tft) {
    int w = 1;
    while (w != SCREEN_WIDTH + 1) {
        tft.drawRect(0, 0, w, SCREEN_HEIGHT, TFT_BLACK);
        w++;
        delay(5);
    }
    textAnimation(tft, " ESP - MEDIA", TFT_WHITE, 4);
}

void textAnimation(TFT_eSPI tft, const char* text, uint16_t color, int size){
    int w = tft.textWidth(text, size);
    int x = -w;
    int wl = 0;

    while(x < SCREEN_WIDTH / 2 - w / 2){
        tft.fillRect(x, 0 , 20, x, TFT_BLACK); 
        tft.drawString(text, x, SCREEN_HEIGHT - 60, size);
        wl+=4;
        x += 4;  
        delay(20);  
    }
}