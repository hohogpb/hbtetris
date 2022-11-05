#include "board.h"
#include <inttypes.h>
#include "draw.h"

typedef struct {
  int width;
  int height;
  int data[];
} board_t;

board_t board = {
    .width = 10,
    .height = 20,
    .data =
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 0
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 1
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 2
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 3
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 4
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 5
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 6
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 7
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 8
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 9
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 10
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 11
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 12
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 13
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 14
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 15
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 16
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 17
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 18
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 19
        },
};

int board_get_cell(int x, int y) {
  if (x < 0 || x >= board.width)
    return -1;
  if (y >= board.height)
    return -1;
  if (y < 0)
    return 0;

  int indx = y * board.width + x;
  int cell = board.data[indx];
  return cell;
}

int board_set_cell(int x, int y, int v) {
  if (x < 0 || x >= board.width)
    return -1;
  if (y < 0 || y >= board.height)
    return -1;

  int indx = y * board.width + x;
  board.data[indx] = v;
  return 0;
}

// 绘制游戏板
void board_draw() {
  for (int y = 0; y < board.height; y++) {
    for (int x = 0; x < board.width; x++) {
      int idx = y * board.width + x;
      int point = board.data[idx];
      int color = point ? fi_cell_color : bk_cell_color;

      draw_board_cell(x, y, color);
    }
  }
}

bool board_check_row_full(int y) {
  for (int x = 0; x < board.width; x++) {
    if (!board_get_cell(x, y))
      return false;
  }
  return true;
}

bool board_check_row_empty(int y) {
  for (int x = 0; x < board.width; x++) {
    if (board_get_cell(x, y))
      return false;
  }
  return true;
}

void board_clear_row(int y) {
  for (int x = 0; x < board.width; x++) {
    board_set_cell(x, y, 0);
  }
}

void board_move_row(int y_dest, int y_src) {
  for (size_t x = 0; x < board.width; x++) {
    int cell = board_get_cell(x, y_src);
    board_set_cell(x, y_dest, cell);
    board_set_cell(x, y_src, 0);
  }
}

int board_find_above_not_empty_row(int y) {
  for (int yy = y - 1; yy >= 0; yy--) {
    if (!board_check_row_empty(yy))
      return yy;
  }
  return -1;
}

void board_check_clear(int* full_rows) {
  for (int y = 0; y < board.height; y++) {
    if (board_check_row_full(y)) {
      board_clear_row(y);
    }
  }

  for (int i = 0; i < board.height; i++) {
    int y = board.height - i;
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

bool board_check_full() {
  // 检测第一行是否有格子
  for (int x = 0; x < board.width; x++) {
    if (board_get_cell(x, 0))
      return true;
  }
  return false;
}

void board_clear() {
  for (int y = 0; y < board.height; y++) {
    for (int x = 0; x < board.width; x++) {
      board_set_cell(x, y, 0);
    }
  }
}
