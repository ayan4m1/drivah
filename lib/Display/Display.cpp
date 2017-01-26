#include "Display.h"

extern uint8_t SevenSegNumFontPlusPlus[];

Display::Display() {
  state = new DisplayState();
  lastTouch = millis();
  gfx = new UTFT(ILI9325D_16, DISP_RS, DISP_WR, DISP_CS, DISP_RST);
  touch = new URTouch(TOUCH_CLK, TOUCH_CS, TOUCH_DIN, TOUCH_DOUT, TOUCH_IRQ);

  gfx->InitLCD(LANDSCAPE);
  touch->InitTouch(LANDSCAPE);
  touch->setPrecision(PREC_LOW);

  gfx->setFont(SevenSegNumFontPlusPlus);
  gfx->setBackColor(VGA_BLACK);
  gfx->setColor(VGA_GREEN);

  gfx->lcdOn();
  gfx->fillScr(VGA_BLACK);
}

void Display::update(uint32_t startMicros) {
  uint32_t currentMs = millis();
  if (currentMs - lastTouch > BACKLIGHT_OFF_MS) {
    analogWrite(BACKLIGHT_PIN, BRIGHTNESS_OFF);
  } else if (currentMs - lastTouch > BACKLIGHT_SLEEP_MS) {
    analogWrite(BACKLIGHT_PIN, BRIGHTNESS_LOW);
  } else {
    analogWrite(BACKLIGHT_PIN, BRIGHTNESS_HIGH);
  }

  if (touch->dataAvailable()) {
    touch->read();
    if (touch->getX() != -1 && touch->getY() != -1) {
      lastTouch = currentMs;
    }
  }

  //uint32_t sumOfSquares = sqrt(pow(state->accel.x, 2) + pow(state->accel.y, 2) + pow(state->accel.z, 2)) / 8192.0;
  gfx->printNumF(state->accel.x / 8192.0, 2, 20, 50);
  gfx->printNumF(state->accel.y / 8192.0, 2, 20, 120);
  gfx->printNumF(state->accel.z / 8192.0, 2, 20, 190);

  /*uint32_t frameTime = (micros() - startMicros);
  if (frameTime < MAX_FRAME_TIME - 20) {
    delayMicroseconds(MAX_FRAME_TIME - frameTime);
  }*/
}

Display::~Display() {
  gfx->clrScr();
  gfx->lcdOff();
  free(gfx);
}
