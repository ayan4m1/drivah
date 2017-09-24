#include <Arduino.h>
#include <Gyroscope.h>
//#include <Display.h>
//#include <Tachometer.h>

VectorInt16 *offsetG = new VectorInt16(70, -65, 40);
VectorInt16 *offsetA = new VectorInt16(-2600, -3400, 1630);

#if SIMULATOR
  float gearRatios[] = { 2.847, 1.552, 1.0, 0.7 };

  #define YARIS_GEARS           4
  #define YARIS_TORQUE_NM       138.3
  #define YARIS_SHIFT_MS        350
  #define YARIS_CDA             0.57
  #define YARIS_MASS_KG         1043
  #define YARIS_ACCEL_MS_SQ     2.63
  #define YARIS_DRAG_AT_100MPH  202.34
  #define YARIS_WHEEL_RADIUS_M  1.969
  #define YARIS_DIFF_RATIO      4.237
  #define YARIS_SHIFT_RPM       3500
  #define YARIS_REDLINE_RPM     7000
  #define YARIS_AVG_L           2.27
  #define YARIS_DIFF_EFF        0.8
  #define AIR_DENSITY           1.225

  struct SimulatorState {
    uint8_t velocity;
    uint8_t gear;
    float throttle;
    float brake;
  };

#endif

Tachometer *tacho;
GearDisplay *gear;
Display *lcd;
Gyroscope *gyro;

#if SIMULATOR
SimulatorState *sim;
#endif

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif

  tacho = new Tachometer();
  gear = new GearDisplay();
  gyro = new Gyroscope(offsetG, offsetA);
  lcd = new Display();

#if SIMULATOR
  sim = new SimulatorState();
#endif
}

#if SIMULATOR

void tickSimulator() {
  uint32_t tickStart = millis();

  if ((sim->throttle * YARIS_REDLINE_RPM) > YARIS_SHIFT_RPM && sim->gear < YARIS_GEARS) {
    delay(YARIS_SHIFT_MS);
    sim->gear++;
    sim->throttle = 0.3;
  } else if (sim->throttle >= 0.8) {
    Serial.println(F("Coast"));
    sim->throttle -= 0.3;
  } else {
    Serial.println(F("Accel"));
    sim->throttle = max((random(5, 10) / 100.0f) + sim->throttle, 1.0);
  }

  float accelStart = millis() - tickStart;

  if (sim->throttle > 0.2) {
    Serial.println(F("Applying torque"));
    float currentTorque = sim->throttle * YARIS_TORQUE_NM;
    float currentGearRatio = gearRatios[sim->gear - 1];
    float force = (currentTorque * currentGearRatio * YARIS_DIFF_RATIO * YARIS_DIFF_EFF) / YARIS_WHEEL_RADIUS_M;
    Serial.println(force);
    sim->velocity += (force / YARIS_MASS_KG) * accelStart;
  } else {
    Serial.println(F("Coasting"));
    float coastDrag = (sim->velocity / 100.0) * YARIS_DRAG_AT_100MPH;
    Serial.println(coastDrag);
    float dragForce = 0.5 * AIR_DENSITY * sim->velocity * YARIS_CDA;
    Serial.println(dragForce);
    sim->velocity -= (dragForce / YARIS_MASS_KG) * accelStart;

    bool downShifted = false;
    if (sim->gear == 4 && (sim->velocity / FPS_TO_MPH) < 50) {
      downShifted = true;
    } else if (sim->gear == 3 && (sim->velocity / FPS_TO_MPH) < 30) {
      downShifted = true;
    } else if (sim->gear == 2 && (sim->velocity / FPS_TO_MPH) < 10) {
      downShifted = true;
    }

    if (downShifted) {
      delay(YARIS_SHIFT_MS);
      sim->gear--;
      Serial.print(F("Downshift to "));
      Serial.println(sim->gear);
    }
  }
}

#endif

void loop() {

  uint32_t started = micros();

#if SIMULATOR
    tickSimulator();
    Serial.print("Speed: ");
    Serial.print(sim->velocity);
    Serial.print(" || Gear: ");
    Serial.print(sim->gear);
    Serial.print(" || RPM: ");
    Serial.print(sim->throttle * YARIS_REDLINE_RPM);
    Serial.print("\n");
#endif

  uint8_t priorGear = sim->gear;
  if (priorGear != sim->gear) {
    gear->gear = sim->gear;
  }

  gear->update();
  tacho->update();

  if (gyro->update()) {
    delay(50);
  }

  lcd->state->rot = gyro->rotation;
  lcd->state->accel = gyro->linAcc;
  lcd->update(started);
}
