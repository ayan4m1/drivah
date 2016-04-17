#include <SPI.h>
#include <Wire.h>
#include <GyroWrapper.h>

#define GYRO_BUFFER_SAMPLES 32
#define GYRO_SAMPLES_KHZ 400
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
  VectorInt16 acceleration;

  Gyroscope(uint8_t, VectorInt16*, VectorInt16*);
  ~Gyroscope();
  bool update();
};
