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

Gyroscope::Gyroscope(uint8_t interruptPin,
                     VectorInt16 *offsetG, VectorInt16 *offsetA) {
  // call the static Wire library setup
  Gyroscope::initWire();

  // init controller and buffer index
  gyro = new MPU6050();

  // init DMP and set offsets
  gyro->dmpInitialize();
  gyro->setXGyroOffset(offsetG->x);
  gyro->setYGyroOffset(offsetG->y);
  gyro->setZGyroOffset(offsetG->z);
  gyro->setXAccelOffset(offsetA->x);
  gyro->setYAccelOffset(offsetA->y);
  gyro->setZAccelOffset(offsetA->z);
  gyro->setDMPEnabled(true);

  // enable and attach interrupt
  this->interruptPin = interruptPin;
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interrupt, RISING);

  int status = gyro->getIntStatus();
  if (status > 0) {
    Serial.println(F("MPU6050 Init Error"));
  }

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
  detachInterrupt(digitalPinToInterrupt(interruptPin));
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
    Serial.println(F("MPU FIFO overflow!"));
  } else if (status & 0x02) {
    // decode our rotation and accel into structs
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
