#include <Arduino.h>

#define DATA_PIN  11
#define LATCH_PIN 12
#define CLOCK_PIN 13

// yes, I have a four-speed. look up the others yourself, rich people.
uint16_t const gearCodes[] = {
  0b11001111, // "1"
  0b10100100, // "2"
  0b10110000, // "3"
  0b10011001  // "4"
};

class GearDisplay {
  uint8_t gear;
public:
  void init();
  void clear();
  void update(uint8_t gear);
};
