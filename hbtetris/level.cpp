#include "level.h"
#include <tchar.h>
#include "fonts.h"
#include "lcd.h"
#include "memdc.h"

int level = 1;

void level_draw() {
  memdc_setfont(fonts_get_text_font());
  memdc_drawtext(L"¼¶±ð", 240, 180, 80, 30, DT_LEFT);

  lcd_draw_num(level, 240, 210, 8);
}
