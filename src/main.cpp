#include <Arduino.h>
#include <esp_task_wdt.h>

#include <Display.hpp>

Display display = Display();
DisplayState state = DisplayState();

#if SIMULATOR
xTaskHandle simTask;
uint16_t totalSeconds = 0;
uint32_t lastTick = 0;
float gearRatios[] = {2.847, 1.552, 1.0, 0.7};

#define GRAVITY_M_S 9.80129
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
#define FPS_TO_MPH(fps) 0.681818 * fps
#define YARIS_WHEEL_CIRCUMFERENCE_M (2 * PI * YARIS_WHEEL_RADIUS_M)
#define RPM_TO_TORQUE(rpm) (rpm * 0.01962) + 15.99117

struct SimulatorState {
  float velocity = 0;
  uint8_t gear = 1;
  float throttle = 0;
  float brake = 0;
} sim;

void tickSimulator(void* params) {
  Serial.println(F(
      "Time,Velocity,Throttle,Gear,RPM,Power (Engine),Power (Wheel),Drag,Lin. "
      "Accel"));

  for (;;) {
    float startingVelocity = sim.velocity;

    if ((sim.throttle * YARIS_REDLINE_RPM) > YARIS_SHIFT_RPM &&
        sim.gear < YARIS_GEARS) {
      delay(YARIS_SHIFT_MS);
      // Serial.printf("Upshift to %d\n", ++sim.gear);
      ++sim.gear;
      if (sim.throttle > 0.2) {
        sim.throttle -= 0.2;
      }
    } else {
      if (sim.throttle < 0.1) {
        bool downShifted = false;
        if (sim.gear == 4 && sim.velocity < 50) {
          downShifted = true;
        } else if (sim.gear == 3 && sim.velocity < 30) {
          downShifted = true;
        } else if (sim.gear == 2 && sim.velocity < 10) {
          downShifted = true;
        }

        if (downShifted) {
          delay(YARIS_SHIFT_MS);
          // Serial.printf("Downshift to %d\n", --sim.gear);
          --sim.gear;
        }
      }

      if (sim.throttle < 1) {
        // int direction = random(-20, 100);
        // if (direction == 0) {
        //   Serial.print(F("Coast @ "));
        // } else if (direction > 0) {
        //   Serial.print(F("Accel @ "));
        // } else {
        //   Serial.print(F("Decel @ "));
        // }
        // sim.throttle =
        //     max(0.0f,
        //         min(((random(1, 3) / 100.0f) * direction) +
        //         sim.throttle, 1.0f));
        sim.throttle += 0.125;
      }
    }

    // Serial.printf("At %.0f%% throttle\n", sim.throttle * 1e2);

    float engineTorque = 0, wheelTorque = 0;
    float engineForce = 0, wheelForce = 0;

    if (sim.throttle > 0) {
      // float currentTorque = sim.throttle * YARIS_TORQUE_NM;
      // float currentGearRatio = gearRatios[sim.gear - 1];
      // float force =
      //     (currentTorque * currentGearRatio * YARIS_DIFF_RATIO *
      //     YARIS_DIFF_EFF) / YARIS_WHEEL_RADIUS_M;
      engineTorque = RPM_TO_TORQUE(sim.throttle * YARIS_REDLINE_RPM);
      wheelTorque = engineTorque / 1.1;
      engineForce = engineTorque / (YARIS_WHEEL_RADIUS_M * sin(90));
      wheelForce = engineForce / 1.1;
      // Serial.printf("Applying %.2f N-m engine torque\n", engineTorque);
      // Serial.printf("Applying %.2f N-m wheel torque\n", wheelTorque);
      sim.velocity += (wheelForce / YARIS_MASS_KG) * 1e2;
    }

    // float coastDrag = (sim.velocity / 1e2) * YARIS_DRAG_AT_100MPH;
    float dragForce = 0.5 * AIR_DENSITY * sim.velocity * YARIS_CDA;
    // Serial.printf("Coasting generated %.2f N-m of drag\n", coastDrag);
    // Serial.printf("Coasting generated %.2f N-m of drag\n", dragForce);
    sim.velocity -= (dragForce / YARIS_MASS_KG) * 1e2;

    uint16_t rpm = (uint16_t)floor(sim.throttle * YARIS_REDLINE_RPM);
    float linearAcceleration = (sim.velocity - startingVelocity) / 1e2;

    state.batteryVoltage = 14.4;
    state.speed = sim.velocity;
    state.rpm = rpm;

    Serial.printf("%d,%.2f,%d,%.2f,%d,%.2f,%.2f,%.2f,%.2f\n", totalSeconds,
                  sim.velocity, rpm, sim.throttle, sim.gear, engineForce,
                  wheelForce, dragForce, linearAcceleration);

    float elapsedMs = millis() - lastTick;

    if (elapsedMs < 1000) {
      vTaskDelay((1000 - elapsedMs) / portTICK_PERIOD_MS);
    }

    totalSeconds++;
    lastTick = millis();
  }
}

#endif

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif

  display.init();

#if SIMULATOR
  xTaskCreatePinnedToCore(tickSimulator, "SIM", 2e6, nullptr, 2, &simTask, 1);
#endif
}

void loop() { display.update(state); }
