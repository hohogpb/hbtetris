#include "spite_queue.h"
#include "block.h"
#include "config.h"
#include "memdc.h"

block_t* next_block = 0;

int next_spite_x = 250;
int next_spite_y = 200;

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
  if (!next_block)
    return;

  for (int y = 0; y < next_block->rows; y++) {
    for (int x = 0; x < next_block->cols; x++) {
      int idx = y * next_block->cols + x;
      int point = next_block->shape[idx];
      int color = point ? fi_cell_color : bk_cell_color;

      next_spite_draw_cell(x, y, color);
    }
  }
}

block_t* spite_queue_get() {
  // ȡ��һ����
  block_t* block = next_block;
  // ���û�У�����һ��
  if (!block)
    block = block_random();

  // ������һ��
  next_block = block_random();
  return block;
}
