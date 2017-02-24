#include "GearDisplay.h"

void GearDisplay::init() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
}

void GearDisplay::clear() {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0);
  digitalWrite(LATCH_PIN, HIGH);
}

void GearDisplay::update(uint8_t gear) {
  this->gear = gear;
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, gearCodes[this->gear - 1]);
  digitalWrite(LATCH_PIN, HIGH);
  delay(300);
}
