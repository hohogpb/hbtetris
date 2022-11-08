#include "level.h"
#include <tchar.h>
#include "memdc.h"

int level = 1;

void level_draw() {
  TCHAR str[256] = {0};
  _stprintf_s(str, L"¼¶±ð: %d", level);

  memdc_drawtext(str, 250, 80);
}
