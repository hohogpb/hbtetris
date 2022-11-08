#include "score.h"
#include <stdio.h>
#include <tchar.h>
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
  
}

void score_draw() {
  TCHAR str[256] = {0};
  _stprintf_s(str, L"ตรทึ:%d", score);

  memdc_drawtext(str, 250, 20);
}
