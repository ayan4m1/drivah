#include "Gyroscope.h"

bool Gyroscope::wired = false;
void Gyroscope::initWire() {
  if (wired) {
    return;
  }

  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
    Wire.setClock(GYRO_SAMPLES_KHZ * KHZ_TO_HZ);
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(GYRO_SAMPLES_KHZ, true);
  #endif
  wired = true;
}

Gyroscope::Gyroscope(VectorInt16 *offsetG, VectorInt16 *offsetA) {
  // call the static Wire library setup
  Gyroscope::initWire();

  // init controller and buffer index
  gyro = new MPU6050();

  // init DMP and set offsets
  uint8_t status = gyro->dmpInitialize();
#if DEBUG
  if (status > 0) {
    Serial.println(F("MPU Init Failed"));
  }
#endif

  gyro->setXGyroOffset(offsetG->x);
  gyro->setYGyroOffset(offsetG->y);
  gyro->setZGyroOffset(offsetG->z);
  gyro->setXAccelOffset(offsetA->x);
  gyro->setYAccelOffset(offsetA->y);
  gyro->setZAccelOffset(offsetA->z);
  gyro->setDMPEnabled(true);

  // enable and attach interrupt
  pinMode(GYRO_INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(GYRO_INTERRUPT_PIN), interrupt, RISING);

  // allocate our packet buffer
  packetSize = gyro->dmpGetFIFOPacketSize();
  buffer = (uint8_t*)malloc(packetSize);
  rotation = Quaternion();
  acceleration = VectorInt16();
}

volatile bool Gyroscope::interruptToggle = false;
void Gyroscope::interrupt() {
  interruptToggle = true;
}

Gyroscope::~Gyroscope() {
  detachInterrupt(digitalPinToInterrupt(GYRO_INTERRUPT_PIN));
  interruptToggle = false;
  free(buffer);
  free(gyro);
}

bool Gyroscope::update() {
  if (!interruptToggle) {
    return false;
  }
  int status = gyro->getIntStatus();

  // first case indicates overflow
  if (status & 0x10) {
    gyro->resetFIFO();
#if DEBUG
    Serial.println(F("MPU FIFO overflow!"));
#endif
  } else if (status & 0x02) {
    // the interrupt should mean that a packet is ready, but if not...
    while (!gyro->dmpPacketAvailable()) {
      delayMicroseconds(10);
    }

    while (gyro->dmpPacketAvailable()) {
      gyro->getFIFOBytes(buffer, packetSize);
    }

    gyro->dmpGetQuaternion(&rotation, buffer);
    gyro->dmpGetAccel(&acceleration, buffer);
    gyro->dmpGetGravity(&gravity, &rotation);
    VectorInt16 linAccel = VectorInt16();
    gyro->dmpGetLinearAccel(&linAccel, &acceleration, &gravity);
    if (linAcc.x > linAccel.x && thresholdCounters[0] < GYRO_THRESHOLD_MAX) {
      thresholdCounters[0]++;
    } else if (linAcc.x > linAccel.x) {
      thresholdCounters[0] = 0;
      linAcc.x = 0;
    }
    if (linAcc.y > linAccel.y && thresholdCounters[1] < GYRO_THRESHOLD_MAX) {
      thresholdCounters[1]++;
    } else if (linAcc.y > linAccel.y) {
      thresholdCounters[1] = 0;
      linAcc.y = 0;
    }
    if (linAcc.z > linAccel.z && thresholdCounters[2] < GYRO_THRESHOLD_MAX) {
      thresholdCounters[2]++;
    } else if (linAcc.z > linAccel.z) {
      thresholdCounters[2] = 0;
      linAcc.z = 0;
    }
    linAcc.x = max(linAcc.x, linAccel.x);
    linAcc.y = max(linAcc.y, linAccel.y);
    linAcc.z = max(linAcc.z, linAccel.z);
  }

  interruptToggle = false;
  return (status & 0x02);
}
