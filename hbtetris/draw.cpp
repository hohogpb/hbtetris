#include "draw.h"
#include <graphics.h>

int cell_width = 20;

// ���Ƹ��ӣ���ͼ����
void draw_cell(int x, int y) {
  rectangle(x, y, x + cell_width, y + cell_width);
  fillrectangle(x + 2, y + 2, x + 2 + cell_width - 4, y + 2 + cell_width - 4);
}

// ����С���飬�߼�����
void draw_board_cell(int col, int row, int color) {
  int spacing = 3;

  int x = col * (cell_width + spacing);
  int y = row * (cell_width + spacing);

  setlinecolor(color);
  setfillcolor(color);

  draw_cell(x, y);
}
