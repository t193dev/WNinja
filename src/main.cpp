
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <SD.h>

#include "config.h"
#include "colors.h"

TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen touch(TOUCH_CS_PIN);

bool sdAvailable = false;

void drawHeader() {
    tft.fillRect(0, 0, 320, 40, WN_PANEL);

    tft.setTextColor(WN_CYAN, WN_PANEL);
    tft.drawString("WNINJA", 12, 8, 4);

    tft.setTextColor(WN_GREY, WN_PANEL);
    tft.drawRightString("v0.1.0", 307, 15, 2);

    tft.drawFastHLine(0, 40, 320, WN_CYAN);
}

void drawTile(int x, int y, const char* name,
              uint16_t color) {

    tft.fillRoundRect(x, y, 145, 65, 7, WN_PANEL);
    tft.drawRoundRect(x, y, 145, 65, 7, color);

    tft.fillRect(x + 9, y + 12, 3, 40, color);

    tft.setTextColor(WN_WHITE, WN_PANEL);
    tft.drawString(name, x + 18, y + 25, 2);
}

void drawDashboard() {
    tft.fillScreen(WN_BG);

    drawHeader();

    tft.setTextColor(WN_WHITE, WN_BG);
    tft.drawString("WIRELESS SECURITY", 12, 48, 2);

    drawTile(10, 70, "WI-FI RADAR", WN_CYAN);
    drawTile(165, 70, "BLE SCANNER", WN_BLUE);

    drawTile(10, 145, "DEAUTH WATCH", WN_AMBER);
    drawTile(165, 145, "DEVICE HUNTER", WN_GREEN);

    tft.fillRect(0, 218, 320, 22, WN_PANEL);

    tft.setTextColor(WN_GREY, WN_PANEL);

    tft.drawString(
        sdAvailable ? "SD: READY" : "SD: NOT FOUND",
        10, 222, 1
    );

    tft.drawRightString("WNINJA ONLINE", 310, 222, 1);
}

void setup() {
    Serial.begin(115200);

    pinMode(TFT_BACKLIGHT, OUTPUT);
    digitalWrite(TFT_BACKLIGHT, HIGH);

    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);

    tft.init();
    tft.setRotation(1);

    touch.begin();
    touch.setRotation(1);

    sdAvailable = SD.begin(SD_CS_PIN, SPI);

    drawDashboard();

    Serial.println("WNinja started");
}

void loop() {
    delay(50);
}
