#include "GearDisplay.h"

GearDisplay::GearDisplay() {
  this->gear = 1;
  this->init();
}

void GearDisplay::init() {
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);

  this->clear();
}

void GearDisplay::clear() {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0);
  digitalWrite(LATCH_PIN, HIGH);
  digitalWrite(RESET_PIN, HIGH);
}

void GearDisplay::update() {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, gearCodes[this->gear - 1]);
  digitalWrite(LATCH_PIN, HIGH);
}
