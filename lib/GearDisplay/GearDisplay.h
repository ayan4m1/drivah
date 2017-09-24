#include <Arduino.h>

#define DATA_PIN  11
#define LATCH_PIN 12
#define CLOCK_PIN 13
#define RESET_PIN 52

// yes, I have a four-speed. look up the others yourself, rich people.
static const uint8_t gearCodes[] = {
  0b11001111, // "1"
  0b10100100, // "2"
  0b10110000, // "3"
  0b10011001, // "4"
  0b11111111  // "0"
};

class GearDisplay {
public:
  uint8_t gear;

  GearDisplay();
  ~GearDisplay();

  void init();
  void clear();
  void update();
};
