#include "Tachometer.h"

void Tachometer::init() {
  pixels = Adafruit_NeoPixel(RING_COUNT, RING_PIN, NEO_GRB + NEO_KHZ800);
  pixels.setBrightness(0x1A);
  pixels.begin();
  pixels.show();
}

void Tachometer::update(float percent) {
  uint8_t pixelCount = pixels.numPixels();
  float val = percent * pixelCount;
  for (int i = 0; i < pixelCount; i++) {
    pixels.setPixelColor(i, (val > 0) ? this->color : 0);
  }
  pixels.show();
}

void Tachometer::setSafe() {
  this->color = pixels.Color(0, 120, 0);
}

void Tachometer::setWarning() {
  this->color = pixels.Color(120, 120, 0);
}

void Tachometer::setDanger() {
  this->color = pixels.Color(150, 0, 0);
}
