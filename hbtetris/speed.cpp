#include "speed.h"
#include <tchar.h>
#include "fonts.h"
#include "lcd.h"
#include "memdc.h"
#include "timer.h"

int speed = 1;

void speed_update() {
  timer1_set_interval(1.0 / speed);
}

void speed_up() {
  speed++;
  speed_update();
}

void speed_draw() {
  memdc_setfont(fonts_get_text_font());
  memdc_drawtext(L"ËÙ¶È", 240, 100, 80, 30, DT_LEFT);

  lcd_draw_num(speed, 240, 130, 888888);
}