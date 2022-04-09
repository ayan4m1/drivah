#include <Arduino.h>

#if SIMULATOR
float gearRatios[] = {2.847, 1.552, 1.0, 0.7};

#define YARIS_GEARS 4
#define YARIS_TORQUE_NM 138.3
#define YARIS_SHIFT_MS 350
#define YARIS_CDA 0.57
#define YARIS_MASS_KG 1043
#define YARIS_ACCEL_MS_SQ 2.63
#define YARIS_DRAG_AT_100MPH 202.34
#define YARIS_WHEEL_RADIUS_M 1.969
#define YARIS_DIFF_RATIO 4.237
#define YARIS_SHIFT_RPM 3500
#define YARIS_REDLINE_RPM 7000
#define YARIS_AVG_L 2.27
#define YARIS_DIFF_EFF 0.8
#define YARIS_WHEELBASE_M 2.50952
#define AIR_DENSITY 1.225
#define FPS_TO_MPH 0.681818
#define YARIS_WHEEL_CIRCUMFERENCE_M (2 * PI * YARIS_WHEEL_RADIUS_M)
#define RPM_TO_TORQUE(rpm) (rpm * 0.01962) + 15.99117

struct SimulatorState {
  uint8_t velocity;
  uint8_t gear;
  float throttle;
  float brake;
} sim;

#endif

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif

#if SIMULATOR
  sim = SimulatorState();
#endif
}

#if SIMULATOR

void tickSimulator() {
  uint32_t tickStart = millis();

  if ((sim.throttle * YARIS_REDLINE_RPM) > YARIS_SHIFT_RPM &&
      sim.gear < YARIS_GEARS) {
    delay(YARIS_SHIFT_MS);
    Serial.printf("Upshift to %d @ ", ++sim.gear);
    sim.throttle -= 0.3;
  } else if (sim.throttle < 1.0) {
    int direction = random(-20, 100);
    if (direction == 0) {
      Serial.print(F("Coast @ "));
    } else if (direction > 0) {
      Serial.print(F("Accel @ "));
    } else {
      Serial.print(F("Decel @ "));
    }
    sim.throttle =
        min((random(1, 3) / 100.0f) * direction + sim.throttle, 1.0f);
  } else {
    sim.throttle = 0.2;
  }

  Serial.printf("%.0f%%\n", sim.throttle * 1e2);

  float accelStart = millis() - tickStart;

  delay(250);

  if (sim.throttle > 0.2) {
    // float currentTorque = sim.throttle * YARIS_TORQUE_NM;
    // float currentGearRatio = gearRatios[sim.gear - 1];
    // float force =
    //     (currentTorque * currentGearRatio * YARIS_DIFF_RATIO *
    //     YARIS_DIFF_EFF) / YARIS_WHEEL_RADIUS_M;
    float force = RPM_TO_TORQUE(sim.throttle * YARIS_REDLINE_RPM);
    float wheelForce = force / 1.1;
    Serial.printf("Applying %.2f N-m engine torque\n", force);
    Serial.printf("Applying %.2f N-m wheel torque\n", wheelForce);
    sim.velocity += (wheelForce / YARIS_MASS_KG) * accelStart;
  }

  // float coastDrag = (sim.velocity / 1e2) * YARIS_DRAG_AT_100MPH;
  float dragForce = 0.5 * AIR_DENSITY * sim.velocity * YARIS_CDA;
  Serial.printf("Coasting generated %.2f N-m of drag\n", dragForce);
  sim.velocity -= (dragForce / YARIS_MASS_KG) * accelStart;

  bool downShifted = false;
  if (sim.gear == 4 && sim.velocity < 22.5) {
    downShifted = true;
  } else if (sim.gear == 3 && sim.velocity < 13.5) {
    downShifted = true;
  } else if (sim.gear == 2 && sim.velocity < 4.5) {
    downShifted = true;
  }

  if (downShifted) {
    delay(YARIS_SHIFT_MS);
    sim.gear--;
    Serial.print(F("Downshift to "));
    Serial.println(sim.gear);
  }
}

#endif

void loop() {
#if SIMULATOR
  tickSimulator();
  Serial.print("Speed: ");
  Serial.print(sim.velocity);
  Serial.print(" || Gear: ");
  Serial.print(sim.gear);
  Serial.print(" || RPM: ");
  Serial.print(sim.throttle * YARIS_REDLINE_RPM);
  Serial.print("\n");
#endif
}
