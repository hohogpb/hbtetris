#include "score.h"
#include <stdio.h>
#include <tchar.h>
#include "fonts.h"
#include "lcd.h"
#include "level.h"
#include "memdc.h"

int score = 0;

void score_reset() {
  score = 0;
}

void score_increace_by_rows(int rows) {
  if (rows == 1) {
    score += 10;
  } else if (rows == 2) {
    score += 30;
  } else if (rows == 3) {
    score += 60;
  } else if (rows == 4) {
    score += 100;
  }

  level_inc_rows(rows);
}

void score_draw() {
  memdc_setfont(fonts_get_text_font());
  memdc_drawtext(L"ตรทึ", 240, 20, 80, 30, DT_LEFT);

  lcd_draw_num(score, 240, 50, 888888);
}
