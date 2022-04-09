#include <Adafruit_NeoPixel.h>
#include <math.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define RING_PIN 52
#define RING_COUNT 16
#define RING_OPTIONS NEO_RGB + NEO_KHZ800
#define RING_BRIGHTNESS 0x1A

#define FPS_TO_MPH 0.681818

class Tachometer {
 private:
  Adafruit_NeoPixel pixels;
  uint32_t color;

  void setWarning();
  void setDanger();
  void setSafe();

 public:
  float percent;

  Tachometer();
  ~Tachometer();

  void init();
  void clear();
  void update();
};
