#include "spite_queue.h"
#include "bag7.h"
#include "block.h"
#include "config.h"
#include "fonts.h"
#include "memdc.h"

// block_t* next_block = 0;

int next_spite_x = 250;
int next_spite_y = 290;

block_t* spite_queue_get() {
  int id = bag7_pick();

  // ȡ��һ����
  block_t* block = block_get(id);
  return block;
}

// ����С���飬�߼�����
void next_spite_draw_cell(int col, int row, int color) {
  int spacing = 1;
  int cell_width = 20;

  int x = col * (cell_width + spacing);
  int y = row * (cell_width + spacing);

  // �������λ��
  x += next_spite_x;
  y += next_spite_y;

  memdc_setlinecolor(color);
  memdc_setfillcolor(color);

  // �������߿�
  memdc_rectangle(x, y, x + cell_width, y + cell_width);
  // ��һ�����أ������ڲ����
  memdc_fillrectangle(x + 2, y + 2, x + 2 + cell_width - 4,
                      y + 2 + cell_width - 4);
}

// ����С���飬�߼�����
void next_spite_draw() {
  memdc_setfont(fonts_get_text_font());
  memdc_drawtext(L"��һ��", 240, 260, 80, 30, DT_LEFT);

  int id = bag7_next();

  // ȡ��һ����
  block_t* block = block_get(id);

  for (int y = 0; y < block->rows; y++) {
    for (int x = 0; x < block->cols; x++) {
      int idx = y * block->cols + x;
      int point = block->shape[idx];
      int color = point ? fi_cell_color : bk_cell_color;

      next_spite_draw_cell(x, y, color);
    }
  }
}
