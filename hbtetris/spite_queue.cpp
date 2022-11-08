#include "spite_queue.h"
#include "block.h"
#include "config.h"
#include "memdc.h"

block_t* next_block = 0;

int next_spite_x = 250;
int next_spite_y = 200;

// 绘制小方块，逻辑层面
void next_spite_draw_cell(int col, int row, int color) {
  int spacing = 1;
  int cell_width = 20;

  int x = col * (cell_width + spacing);
  int y = row * (cell_width + spacing);

  // 考虑面板位置
  x += next_spite_x;
  y += next_spite_y;

  memdc_setlinecolor(color);
  memdc_setfillcolor(color);

  // 绘制外侧边框
  memdc_rectangle(x, y, x + cell_width, y + cell_width);
  // 格一个像素，绘制内测填充
  memdc_fillrectangle(x + 2, y + 2, x + 2 + cell_width - 4,
                      y + 2 + cell_width - 4);
}

// 绘制小方块，逻辑层面
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
  // 取下一个块
  block_t* block = next_block;
  // 如果没有，生成一个
  if (!block)
    block = block_random();

  // 更新下一块
  next_block = block_random();
  return block;
}
