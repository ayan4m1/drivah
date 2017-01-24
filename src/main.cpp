#include <Arduino.h>
#include <Gyroscope.h>
#include <Display.h>

VectorInt16 *offsetG = new VectorInt16(70, -65, 40);
VectorInt16 *offsetA = new VectorInt16(-2600, -3400, 1630);

Display *lcd;
Gyroscope *gyro;

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  Serial.println(F("Gyro init started"));
#endif

  gyro = new Gyroscope(offsetG, offsetA);
  lcd = new Display();
}

void loop() {
  uint32_t started = micros();

  if (gyro->update()) {
    return;
  }

  lcd->state->rot = gyro->rotation;
  lcd->state->accel = gyro->linAcc;
  lcd->update(started);
}
