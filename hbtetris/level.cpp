#include "level.h"
#include <tchar.h>
#include "fonts.h"
#include "lcd.h"
#include "memdc.h"
#include "speed.h"

int level = 1;

// 升级需要行数
const int level_up_rows = 30;

int level_up_counter = 0;

int level_get() {
  return level;
}

void level_draw() {
  memdc_setfont(fonts_get_text_font());
  memdc_drawtext(L"级别", 240, 180, 80, 30, DT_LEFT);

  lcd_draw_num(level, 240, 210, 8);
}

void level_up() {
  level++;
  speed_up();
}

void level_inc_rows(int rows) {
  level_up_counter += rows;
  if (level_up_counter > level_up_rows) {
    level_up();
    level_up_counter -= level_up_rows;
  }
}

void level_init() {
  level = 1;
  level_up_counter = 0;
}

void level_reset() {
  level_init();
}
