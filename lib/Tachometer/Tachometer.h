#include <math.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define RING_PIN 43
#define RING_COUNT 16

#define RING_CONTRAST 0x05
#define RING_BRIGHTNESS 0x1A

#define FPS_TO_MPH 0.681818

class Tachometer {
  Adafruit_NeoPixel pixels;
  uint32_t color;
  float percent;
  bool warning;
  bool danger;
public:
  void init();
  void update(float percent);
  void setWarning();
  void setDanger();
  void setSafe();
};
