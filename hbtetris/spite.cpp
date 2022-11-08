#include "spite.h"
#include <stdlib.h>
#include "block.h"
#include "board.h"
#include "config.h"
#include "spite_queue.h"

int spite_x = 0;
int spite_y = 0;
block_t* spite_block;

void spite_new() {
  spite_block = spite_queue_get();

  int board_cols = board_get_cols();

  spite_x = (board_cols - spite_block->cols) / 2;
  spite_y = -4;
}

int spite_get_x() {
  return spite_x;
}

int spite_get_y() {
  return spite_y;
}

void spite_move_left() {
  spite_x--;
}

void spite_move_right() {
  spite_x++;
}

void spite_move_up() {
  spite_y--;
}

void spite_move_down() {
  spite_y++;
}

int spite_get_cell(int x, int y) {
  return block_get_cell(spite_block, x, y);
}

bool spite_some_cell(int dx, int dy, bool (*predicate)(int, int)) {
  return block_some_cell(spite_block, dx, dy, predicate);
}

void spite_foreach_cell(int dx, int dy, void (*predicate)(int, int)) {
  block_foreach_cell(spite_block, dx, dy, predicate);
}

bool spite_can_move_left() {
  return !spite_some_cell(+spite_x - 1, +spite_y, board_collison);
}

bool spite_can_move_right() {
  return !spite_some_cell(+spite_x + 1, +spite_y, board_collison);
}

bool spite_can_move_down() {
  return !spite_some_cell(+spite_x, +spite_y + 1, board_collison);
}

block_t* spite_get_rotate_shape() {
  return block_get_rotate_shape(spite_block);
}

void spite_rotate() {
  block_t* ratate_block = spite_get_rotate_shape();
  spite_block = ratate_block;
}

bool spite_can_rotate() {
  block_t* rotate_spite = spite_get_rotate_shape();
  return !block_some_cell(rotate_spite, +spite_x, +spite_y, board_collison);
}

void spite_draw() {
  int* spite_shape = spite_block->shape;
  int spite_width = spite_block->cols;
  int spite_height = spite_block->rows;

  for (int y = 0; y < spite_height; y++) {
    for (int x = 0; x < spite_width; x++) {
      int idx = y * spite_width + x;
      int point = spite_shape[idx];
      if (point) {
        board_draw_cell_clip(spite_x + x, spite_y + y, fi_cell_color);
      }
    }
  }
}
