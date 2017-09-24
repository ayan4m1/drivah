#include "Tachometer.h"

Tachometer::Tachometer() {
  pixels = Adafruit_NeoPixel(RING_COUNT, RING_PIN, RING_OPTIONS);
  this->init();
}

void Tachometer::init() {
  pixels.setBrightness(RING_BRIGHTNESS);
  pixels.begin();

  this->setSafe();
  this->clear();
}

void Tachometer::clear() {
  uint8_t pixelCount = pixels.numPixels();
  for (uint8_t i = 0; i < pixelCount; i++) {
    pixels.setPixelColor(i, 0);
  }
  pixels.show();
}

void Tachometer::update() {
  if (this->percent >= 0.8) {
    this->setDanger();
  } else if (this->percent >= 0.6) {
    this->setWarning();
  } else {
    this->setSafe();
  }

  uint8_t pixelCount = pixels.numPixels();
  uint8_t lastActivePixel = floor(percent * pixelCount);
  for (uint8_t i = 0; i < pixelCount; i++) {
    if (i < lastActivePixel) {
      pixels.setPixelColor(i, this->color);
    } else {
      pixels.setPixelColor(i, 0);
    }
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
