#include "spite.h"
#include "draw.h"
#include "shape.h"

const int spite_width = 4;
const int spite_height = 4;

int spite_block_id = 'Z';
int spite_block_sub_id = 0;
int spite_x = 0;
int spite_y = 0;

void spite_new() {
  block_t* block = block_get('I');  // block_random();

  spite_block_id = block->id;
  spite_block_sub_id = 0;
  spite_x = 3;
  spite_y = -3;
}

void spite_draw() {
  int* spite_shape = block_get_shape(spite_block_id, spite_block_sub_id);

  for (int y = 0; y < spite_height; y++) {
    for (int x = 0; x < spite_width; x++) {
      int idx = y * spite_width + x;
      int point = spite_shape[idx];
      if (point) {
        draw_board_cell(spite_x + x, spite_y + y, fi_cell_color);
      }
    }
  }
}

void spite_get_rotate_id(int* id, int* subid) {
  int new_sub_id = block_get_rotate_shape(spite_block_id, spite_block_sub_id);
  *id = spite_block_id;
  *subid = new_sub_id;
}

int* spite_get_rotate_shape() {
  int* shape = block_get_shape(spite_block_id, spite_block_sub_id);
  return shape;
}

void spite_rotate() {
  int new_sub_id = block_get_rotate_shape(spite_block_id, spite_block_sub_id);
  spite_block_sub_id = new_sub_id;
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
  int* spite_shape = block_get_shape(spite_block_id, spite_block_sub_id);
  return spite_shape[y * spite_width + x];
}

int spite_get_x() {
  return spite_x;
}

int spite_get_y() {
  return spite_y;
}

int spite_get_id() {
  return spite_block_id;
}

int spite_get_sub_id() {
  return spite_block_sub_id;
}

/**
 * 判断是否一个有效格子满足条件.
 *
 * \param predicate 判断回调
 * \return
 */
bool spite_some_cell(bool (*predicate)(int, int)) {
  int* spite_shape = block_get_shape(spite_block_id, spite_block_sub_id);

  for (int y = 0; y < spite_height; y++) {
    for (int x = 0; x < spite_width; x++) {
      int idx = y * spite_width + x;
      int cell = spite_shape[idx];
      // 非有效格子
      if (!cell)
        continue;

      if (predicate(x, y)) {
        return true;
      }
    }
  }
  return false;
}

/**
 * 判断是否一个有效格子满足条件.
 *
 * \param predicate 判断回调
 * \return
 */
void spite_foreach_cell(void (*predicate)(int, int)) {
  int* spite_shape = block_get_shape(spite_block_id, spite_block_sub_id);

  for (int y = 0; y < spite_height; y++) {
    for (int x = 0; x < spite_width; x++) {
      int idx = y * spite_width + x;
      int cell = spite_shape[idx];
      if (!cell)
        continue;

      predicate(x, y);
    }
  }
}