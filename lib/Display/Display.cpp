#include "Display.hpp"

using namespace gfx;

open_font &Display::font = Cheva_Display_Demo_ttf;
Display::lcd_type Display::lcd;
Display::frame_buffer_type Display::bg;
Display::frame_buffer_type Display::fg;
bool Display::displayFg = true;

bool Display::init() {
  auto state = lcd.initialize();
  if (!state) {
    return false;
  }

  lcd.clear(lcd.bounds());

  draw::filled_rectangle(bg, (srect16)bg.bounds(), bmp_color::black);
  draw::filled_rounded_rectangle(bg, (srect16)bg.bounds(), 0.3,
                                 bmp_color::indian_red);

  return true;
}

void Display::update(const DisplayState state) {
  const float fontScale = font.scale(32);

  frame_buffer_type *currentBuffer = (displayFg) ? &fg : &bg;
  displayFg = !displayFg;

  char buf[16];
  sprintf(buf, "%d rpm", state.rpm);

  draw::text(currentBuffer, srect16(0, 0, 320, 240), spoint16(0, 0),
             (const char *)buf, font, fontScale, frame_buffer_color::white,
             frame_buffer_color::indian_red, false);

  sprintf(buf, "%d mph", state.speed);

  draw::text(currentBuffer, srect16(0, 0, 320, 240), spoint16(0, 40),
             (const char *)buf, font, fontScale, frame_buffer_color::white,
             frame_buffer_color::indian_red, false);

  sprintf(buf, "%.1f V", state.batteryVoltage);

  draw::text(currentBuffer, srect16(0, 0, 320, 240), spoint16(0, 80),
             (const char *)buf, font, fontScale, frame_buffer_color::white,
             frame_buffer_color::indian_red, false);
}
