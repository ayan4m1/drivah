#include <UTFT.h>
#include <URTouch.h>
#include <helper_3dmath.h>

struct DisplayState {
  VectorInt16 accel;
  Quaternion rot;
};

class Display {
public:
  DisplayState *state;
  Display();
  ~Display();
  void update(uint32_t);
private:
  UTFT *gfx;
  URTouch *touch;
  uint32_t lastTouch;
  float sampleBuffer[24] = {};
  uint8_t sampleIndex = 0;
};

#define DISP_RST 41
#define DISP_CS  40
#define DISP_WR  39
#define DISP_RS  38

#define TOUCH_CLK  11
#define TOUCH_CS   10
#define TOUCH_DIN  9
#define TOUCH_DOUT 8
#define TOUCH_IRQ  7

#define DISP_FRAME_RATE 8
#define DISP_WIDTH 240
#define DISP_HEIGHT 320

#define SECONDS_TO_US 1000000L
#define MAX_FRAME_TIME SECONDS_TO_US / DISP_FRAME_RATE

#define BACKLIGHT_SLEEP_MS 5000

#define BRIGHTNESS_OFF 0
#define BRIGHTNESS_LOW 4
#define BRIGHTNESS_HIGH 16
