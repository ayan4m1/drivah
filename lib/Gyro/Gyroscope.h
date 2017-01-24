#include <SPI.h>
#include <Wire.h>
#include <MPU6050.h>

#define GYRO_INTERRUPT_PIN 2
#define GYRO_BUFFER_SAMPLES 96
#define GYRO_SAMPLES_KHZ 400
#define GYRO_THRESHOLD_MAX 100
#define KHZ_TO_HZ 1000L

class Gyroscope {
private:
  MPU6050 *gyro;
  uint8_t interruptPin;

  static bool wired;
  static void initWire();

  static void interrupt();
  static volatile bool interruptToggle;

  uint8_t *buffer;
  uint8_t bufferIdx;
  uint8_t packetSize;
public:
  Quaternion rotation;
  VectorFloat gravity;
  VectorInt16 acceleration;
  VectorInt16 linAcc;
  VectorFloat maxAccel;
  uint16_t thresholdCounters[3] = { 0, 0, 0 };

  Gyroscope(VectorInt16*, VectorInt16*);
  ~Gyroscope();
  bool update();
};
