#include "speed.h"
#include <tchar.h>
#include "memdc.h"
#include "timer.h"

int speed = 1;

void speed_draw() {
  TCHAR str[256] = {0};
  _stprintf_s(str, L"ËÙ¶È: %d", speed);

  memdc_drawtext(str, 250, 50);
}

void speed_inc() {
  speed += 1;
  speed_update();
}

void speed_update() {
  timer1_set_interval(1.0 / speed);
}
