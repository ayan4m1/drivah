#include <Arduino.h>
#include <Gyroscope.h>
#include <Display.h>
#include <Tachometer.h>
#include <GearDisplay.h>

VectorInt16 *offsetG = new VectorInt16(70, -65, 40);
VectorInt16 *offsetA = new VectorInt16(-2600, -3400, 1630);

#ifdef SIMULATOR
  #define SHIFT_MS 120
  #define COAST_MS 20000
  #define GEAR_COUNT 4

  #define TESLA_ACCEL  38.3
  #define SPORTS_ACCEL 31.5
  #define LUXURY_ACCEL 13

  #define YARIS_CD    0.29
  #define YARIS_ACCEL 8.48
#endif

Tachometer *tacho;
GearDisplay *gear;
Display *lcd;
Gyroscope *gyro;

float rpm = 0.0;
float currentAccel = 0.0;
uint8_t currentSpeed = 0;
uint8_t currentGear = 1;
uint32_t shiftMs = 0;
uint32_t accelStart = 0;
uint32_t coastStart = 0;
uint32_t loopDelta = 0;
uint32_t totalTravel = 0;

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  Serial.println(F("Gyro init started"));
#endif

  tacho = new Tachometer();
  gear = new GearDisplay();
  gyro = new Gyroscope(offsetG, offsetA);
  lcd = new Display();

  tacho->init();
  gear->init();
}

void loop() {
  uint32_t started = micros();

  if (gyro->update()) {
    return;
  }

  #ifdef SIMULATOR
    if (rpm > 0.8 && currentGear < GEAR_COUNT) {
      shiftMs = millis() - shiftMs;
      Serial.write("Upshift lag\n");
      if (shiftMs > SHIFT_MS) {
        Serial.write("Shifted up\n");
        shiftMs = 0;
        rpm = 0.3;
        currentGear++;
      }
    }

    if (rpm < 0.95) {
      rpm = max((random(10, 25) / 100.0f) + rpm, 1.0);
      Serial.write("Accel\n");
      accelStart = millis() - accelStart;
      if (rpm > 0.2) {
        // ft/s^2 based on engine load (linear, simplistic)
        currentAccel = YARIS_ACCEL * rpm;
        // ft/s
        currentSpeed = currentAccel * (loopDelta / 1000.0f);
        // ft
        totalTravel += currentSpeed * (loopDelta / 1000.0f);
      }
    } else {
      // coast for 20 seconds
      Serial.write("Coasting\n");
      coastStart = millis() - coastStart;
      if (coastStart > COAST_MS) {
        coastStart = 0;
        rpm = 0.3;
      }
    }

    if ((currentSpeed / FPS_TO_MPH) < 5) {
      currentGear = 1;
      Serial.write("Downshift to 1\n");
    } else if ((currentSpeed / FPS_TO_MPH) < 30) {
      currentGear = 2;
      Serial.write("Downshift to 2\n");
    } else if ((currentSpeed / FPS_TO_MPH) < 50) {
      currentGear = 3;
      Serial.write("Downshift to 3\n");
    }
  #endif

    if (rpm > 0.8) {
      tacho->setWarning();
    } else if (rpm >= 0.9) {
      tacho->setDanger();
    } else {
      tacho->setSafe();
    }

    tacho->update(rpm);
    gear->update(currentGear);

  #ifdef SIMULATOR
    loopDelta = millis();
  #endif

  lcd->state->rot = gyro->rotation;
  lcd->state->accel = gyro->linAcc;
  lcd->update(started);
}
