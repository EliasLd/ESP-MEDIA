#define SCREEN_WIDTH 340
#define SCREEN_HEIGHT 240

void boot_animation(TFT_eSPI tft) {
    int w = 1;
    while (w != SCREEN_WIDTH) {
        tft.drawRect(0, 0, w, SCREEN_HEIGHT, TFT_BLACK);
        w++;
        delay(5);
    }
}

