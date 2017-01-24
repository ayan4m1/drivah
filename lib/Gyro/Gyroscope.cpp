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
  buffer = (uint8_t*)malloc(packetSize * GYRO_BUFFER_SAMPLES);
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

    gyro->getFIFOBytes(buffer, packetSize);
    gyro->dmpGetQuaternion(&rotation, buffer);
    gyro->dmpGetAccel(&acceleration, buffer);
  }

  interruptToggle = false;
  return (status & 0x02);
}
