#include "Display.h"

extern uint8_t SmallFont[];

Display::Display() {
  state = new DisplayState();
  lastTouch = millis();
  gfx = new UTFT(ILI9325D_16, DISP_RS, DISP_WR, DISP_CS, DISP_RST);
  touch = new URTouch(TOUCH_CLK, TOUCH_CS, TOUCH_DIN, TOUCH_DOUT, TOUCH_IRQ);

  gfx->InitLCD(LANDSCAPE);
  touch->InitTouch(LANDSCAPE);
  touch->setPrecision(PREC_MEDIUM);

  gfx->setFont(SmallFont);
  gfx->setBackColor(VGA_BLACK);
  gfx->setColor(VGA_GREEN);

  gfx->lcdOn();
  gfx->fillScr(VGA_BLACK);
}

void Display::update(uint32_t startMicros) {
  uint32_t currentMs = millis();
  if (currentMs - lastTouch > BACKLIGHT_SLEEP_MS) {
    analogWrite(4, 20);
  } else {
    analogWrite(4, 200);
  }

  if (touch->dataAvailable()) {
    touch->read();
    if (touch->getX() != -1 && touch->getY() != -1) {
      lastTouch = currentMs;
      gfx->print(F("TOUCHING"), 0, 50);
      gfx->printNumI(touch->getX(), 100, 50);
      gfx->printNumI(touch->getY(), 150, 50);
    }
  } else {
    gfx->setColor(VGA_BLACK);
    gfx->fillRect(0, 50, DISP_WIDTH, 68);
    gfx->setColor(VGA_GREEN);
  }

  gfx->print(F("X"), 0, 100);
  gfx->printNumF(state->accel.x / 8192.0, 2, 20, 100);
  gfx->print(F("Y"), 0, 150);
  gfx->printNumF(state->accel.y / 8192.0, 2, 20, 150);
  gfx->print(F("Z"), 0, 200);
  gfx->printNumF(state->accel.z / 8192.0, 2, 20, 200);

  uint32_t frameTime = (micros() - startMicros);
  if (frameTime < MAX_FRAME_TIME - 20) {
    delayMicroseconds(MAX_FRAME_TIME - frameTime);
  }
}

Display::~Display() {
  gfx->clrScr();
  gfx->lcdOff();
  free(gfx);
}
