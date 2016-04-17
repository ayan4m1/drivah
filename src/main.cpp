#include <Arduino.h>
#include <Gyroscope.h>

#define GYRO_INTERRUPT_PIN 2
VectorInt16 *offsetG = new VectorInt16(71, -62, 46);
VectorInt16 *offsetA = new VectorInt16(-2442, -3385, 1632);
Gyroscope *gyro;

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  Serial.println(F("Gyro init started"));
#endif

  gyro = new Gyroscope(GYRO_INTERRUPT_PIN, offsetG, offsetA);
}

void loop() {
  if (gyro->update()) {
    Serial.print(gyro->acceleration.x);
    Serial.print('\t');
    Serial.print(gyro->acceleration.y);
    Serial.print('\t');
    Serial.print(gyro->acceleration.z);
    Serial.print(" A||G ");
    Serial.print(gyro->rotation.w);
    Serial.print('\t');
    Serial.print(gyro->rotation.x);
    Serial.print('\t');
    Serial.print(gyro->rotation.y);
    Serial.print('\t');
    Serial.println(gyro->rotation.z);
  }
}
