#include "lcd.h"
#include <tchar.h>
#include "config.h"
#include "fonts.h"
#include "memdc.h"

#define LCD_BKCOLOR RGB(118, 131, 100)

void lcd_draw_num(int num, int x, int y, int bk) {
  TCHAR numstr[32] = {0};

  memdc_setfont(fonts_get_lcd_font());

  int old_color = memdc_settextcolor(LCD_BKCOLOR);

  _stprintf_s(numstr, L"%d", bk);
  memdc_drawtext(numstr, x, y, 100, 50, DT_RIGHT);


  _stprintf_s(numstr, L"%d", num);

  memdc_settextcolor(fi_cell_color);
  memdc_drawtext(numstr, x, y, 100, 50, DT_RIGHT);

  memdc_settextcolor(old_color);
}
