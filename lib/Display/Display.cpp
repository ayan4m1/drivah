#include "Display.h"

extern uint8_t SmallFont[];

Display::Display() {
  state = new DisplayState();
  lastTouch = millis();
  gfx = new UTFT(ILI9325D_16, DISP_RS, DISP_WR, DISP_CS, DISP_RST);
  touch = new URTouch(TOUCH_CLK, TOUCH_CS, TOUCH_DIN, TOUCH_DOUT, TOUCH_IRQ);

  gfx->InitLCD(LANDSCAPE);
  touch->InitTouch(LANDSCAPE);

  gfx->setFont(SmallFont);
  gfx->setBackColor(VGA_BLACK);
  gfx->setColor(VGA_GREEN);

  gfx->lcdOn();
  gfx->fillScr(VGA_BLACK);
}

void Display::update(uint32_t startMicros) {
  uint32_t currentMs = millis();
  if (currentMs - lastTouch > BACKLIGHT_SLEEP_MS) {
    gfx->setBrightness(BRIGHTNESS_OFF);
  } else {
    gfx->setBrightness(BRIGHTNESS_HIGH);
  }

  if (touch->dataAvailable()) {
    touch->read();
    lastTouch = currentMs;
  }

  gfx->setColor(VGA_BLACK);
  gfx->fillRect(0, 0, DISP_WIDTH, 70);
  gfx->fillRect(0, 100, DISP_WIDTH / 4, 150);
  gfx->setColor(VGA_GREEN);

  gfx->printNumF(state->rot.w, 1, 10, 50);
  gfx->printNumF(state->rot.x, 1, 50, 50);
  gfx->printNumF(state->rot.y, 1, 120, 50);
  gfx->printNumF(state->rot.z, 1, 170, 50);

  gfx->printNumF(state->accel.x, 2, 10, 100);
  gfx->printNumF(state->accel.y, 2, 10, 150);
  gfx->printNumF(state->accel.z, 2, 10, 200);

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
