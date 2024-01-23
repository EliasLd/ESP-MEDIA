#define SCREEN_HEIGHT 320
#define SCREEN_WIDTH 240

void bootAnimation(TFT_eSPI tft);
void textAnimation(TFT_eSPI tft, const char* text, uint16_t color, int size);
void chargement(TFT_eSPI tft);

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

void chargement(TFT_eSPI tft, uint32_t color){
    tft.fillScreen(TFT_BLACK);

    int x0 = SCREEN_WIDTH / 3, y0 = SCREEN_HEIGHT / 2;
    int x1 = SCREEN_WIDTH / 2, y1 = SCREEN_HEIGHT / 3;
    int xz = SCREEN_WIDTH - x0, yz = SCREEN_HEIGHT - y1;

    int xc = x0, yc = y0;

    unsigned long start = millis();
    const long duration = 5000;
    unsigned long current = start;
    bool sw = false;
    const char* str = "LOADING";
    int w = tft.textWidth(str, 4);
    int xw = SCREEN_WIDTH / 2 - w/2;
    tft.drawString(str, xw, SCREEN_HEIGHT - 60, 4);
    u_int32_t bgcol;
    

    while(current - start < duration){
        //animation du cercle de chargement
        //Tracé du losange dans le sens indirect
        if(xc < xz && !sw){
            color = TFT_BLACK;
            bgcol = TFT_YELLOW;
            if(yc > y1 && xc < x1){
                xc+=2;
                yc--;
            }
            else if(yc < y0){
                xc+=2;
                yc++;
            }
        }
        else if(yc < yz && xc > x1){
            color = TFT_ORANGE;
            bgcol = TFT_ORANGE;
            sw = true;
            xc-=2;
            yc++;
        }
        else{
            color = TFT_YELLOW;
            bgcol = TFT_ORANGE;
            xc-=2;
            yc--;
        }
        if(xc <= x0 && yc <= y0){
            sw = false;
            tft.fillScreen(TFT_BLACK);
            tft.drawString(str, xw, SCREEN_HEIGHT - 60, 4);
        }
    
        tft.fillCircle(xc, yc, 5, bgcol);
        current = millis();
        delay(8);
    }
}