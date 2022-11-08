#include "board.h"
#include <inttypes.h>
#include "config.h"
#include "memdc.h"

typedef struct {
  int cols;
  int rows;
  int* data;
  int x;
  int y;
  int cell_spacing;
  int cell_width;
} board_t;

int board_data[20 * 10] = {0};

board_t board = {
    .cols = 10,
    .rows = 20,
    .data = board_data,
    .x = 10,
    .y = 10,
    .cell_spacing = 1,
    .cell_width = 20,
};

// 面板行数
int board_get_rows() {
  return board.rows;
}

// 面板列数
int board_get_cols() {
  return board.cols;
}

// 面板清空
void board_clear() {
  for (int y = 0; y < board.rows; y++) {
    for (int x = 0; x < board.cols; x++) {
      board_set_cell(x, y, 0);
    }
  }
}

// 获取格子数据
int board_get_cell(int x, int y) {
  if (x < 0 || x >= board.cols)
    return -1;
  if (y >= board.rows)
    return -1;
  if (y < 0)
    return 0;

  int indx = y * board.cols + x;
  int cell = board.data[indx];
  return cell;
}

// 设置格子数据
int board_set_cell(int x, int y, int v) {
  if (x < 0 || x >= board.cols)
    return -1;
  if (y < 0 || y >= board.rows)
    return -1;

  int indx = y * board.cols + x;
  board.data[indx] = v;
  return 0;
}

void board_fill_cell(int x, int y) {
  if (x < 0 || x >= board.cols)
    return;
  if (y < 0 || y >= board.rows)
    return;

  int indx = y * board.cols + x;
  board.data[indx] = 1;
}

// 检测某一行是否都有值
bool board_check_row_full(int y) {
  for (int x = 0; x < board.cols; x++) {
    if (!board_get_cell(x, y))
      return false;
  }
  return true;
}

// 检测某一行是否为空
bool board_check_row_empty(int y) {
  for (int x = 0; x < board.cols; x++) {
    if (board_get_cell(x, y))
      return false;
  }
  return true;
}

// 清空某一行
void board_clear_row(int y) {
  for (int x = 0; x < board.cols; x++) {
    board_set_cell(x, y, 0);
  }
}

// 填充某一行
void board_fill_row(int y) {
  for (int x = 0; x < board.cols; x++) {
    board_set_cell(x, y, 1);
  }
}

// 移动一行到另外一行，并清空被移动的那行
void board_move_row(int y_dest, int y_src) {
  for (int x = 0; x < board.cols; x++) {
    int cell = board_get_cell(x, y_src);
    board_set_cell(x, y_dest, cell);
    board_set_cell(x, y_src, 0);
  }
}

// 找到某行上面第一个不为空的行
int board_find_above_not_empty_row(int y) {
  for (int yy = y - 1; yy >= 0; yy--) {
    if (!board_check_row_empty(yy))
      return yy;
  }
  return -1;
}

// 找到所有满了的行
int board_get_full_rows(int* full_rows) {
  int count = 0;
  for (int y = 0; y < board.rows; y++) {
    if (board_check_row_full(y)) {
      full_rows[count] = y;
      count++;
    }
  }
  return count;
}

void board_check_clear(int* full_rows) {
  for (int y = 0; y < board.rows; y++) {
    if (board_check_row_full(y)) {
      board_clear_row(y);
    }
  }

  for (int i = 0; i < board.rows; i++) {
    int y = board.rows - i;
    if (board_check_row_empty(y)) {
      int not_empty_y = board_find_above_not_empty_row(y);
      // 如果上面已经没有有数据的行，则可以退出了
      if (not_empty_y < 0)
        break;
      // 否则移动行
      board_move_row(y, not_empty_y);
    }
  }
}

// 检测面板是否已经满了
bool board_check_full() {
  // 检测第一行是否有格子
  for (int x = 0; x < board.cols; x++) {
    if (board_get_cell(x, 0))
      return true;
  }
  return false;
}

// 填充给定的行号
void board_fill_rows(int* rows, int count) {
  for (int i = 0; i < count; i++) {
    int y = rows[i];
    board_fill_row(y);
  }
}

// 清空给定的行号
void board_clear_rows(int* rows, int count) {
  for (int i = 0; i < count; i++) {
    int y = rows[i];
    board_clear_row(y);
  }
}

bool board_collison(int x, int y) {
  return board_get_cell(x, y);
}

void board_draw_row(int y, int color) {
  for (int x = 0; x < board.cols; x++) {
    int idx = y * board.cols + x;
    int point = board.data[idx];
    board_draw_cell(x, y, color);
  }
}

void board_draw_rows(int* rows, int count, int color) {
  for (int n = 0; n < count; n++) {
    int y = rows[n];
    board_draw_row(y, color);
  }
}

// 闪烁行列表
void board_blink_rows(int* rows, int count) {
  for (int i = 0; i < 3; i++) {
    // board_clear_rows(rows, count);
    // board_draw();
    board_draw_rows(rows, count, bk_cell_color);
    memdc_swap();
    Sleep(100);

    // board_fill_rows(rows, count);
    // board_draw();
    board_draw_rows(rows, count, fi_cell_color);
    memdc_swap();
    Sleep(100);
  }
}

// 绘制小方块，逻辑层面
void board_draw_cell(int col, int row, int color) {
  int spacing = board.cell_spacing;
  int cell_width = board.cell_width;

  int x = col * (cell_width + spacing);
  int y = row * (cell_width + spacing);

  // 考虑面板位置
  x += board.x;
  y += board.y;

  memdc_setlinecolor(color);
  memdc_setfillcolor(color);

  // 绘制外侧边框
  memdc_rectangle(x, y, x + cell_width, y + cell_width);
  // 格一个像素，绘制内测填充
  memdc_fillrectangle(x + 2, y + 2, x + 2 + cell_width - 4,
                      y + 2 + cell_width - 4);
}

// 绘制小方块，非范围内的裁剪
void board_draw_cell_clip(int col, int row, int color) {
  if (col < 0 || col >= board.cols || row < 0 || row >= board.rows)
    return;
  board_draw_cell(col, row, color);
}

void board_draw_all_cells() {
  for (int y = 0; y < board.rows; y++) {
    for (int x = 0; x < board.cols; x++) {
      int idx = y * board.cols + x;
      int point = board.data[idx];
      int color = point ? fi_cell_color : bk_cell_color;

      board_draw_cell(x, y, color);
    }
  }
}

void board_draw_valid_cells() {
  for (int y = 0; y < board.rows; y++) {
    for (int x = 0; x < board.cols; x++) {
      int idx = y * board.cols + x;
      int point = board.data[idx];
      if (!point)
        continue;

      board_draw_cell(x, y, fi_cell_color);
    }
  }
}

// 绘制游戏板基本面
void board_draw_base() {
  //
  memdc_setlinecolor(fi_cell_color);

  int rect_x = board.x - 5;
  int rect_y = board.y - 5;
  int rect_right =
      board.x + board.cols * (board.cell_width + board.cell_spacing) + 4;
  int rect_bottom =
      board.y + board.rows * (board.cell_width + board.cell_spacing) + 4;

  // 绘制外侧边框
  memdc_rectangle(rect_x, rect_y, rect_right, rect_bottom);

  for (int y = 0; y < board.rows; y++) {
    for (int x = 0; x < board.cols; x++) {
      int idx = y * board.cols + x;
      int point = board.data[idx];
      int color = bk_cell_color;
      board_draw_cell(x, y, color);
    }
  }
}

void board_gameover_animation() {
  for (int y = board.rows-1; y >= 0; y--) {
    board_draw_row(y, fi_cell_color);
    memdc_swap();
    Sleep(20);
  }

  for (int y = 0; y < board.rows; y++) {
    board_draw_row(y, bk_cell_color);
    memdc_swap();
    Sleep(20);
  }
}
