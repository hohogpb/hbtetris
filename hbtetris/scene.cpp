#include "scene.h"
#include <graphics.h>
#include <stdio.h>
#include "board.h"
#include "draw.h"
#include "shape.h"
#include "spite.h"
#include "timer.h"

void scene_draw() {
  BeginBatchDraw();

  setbkcolor(bk_color);
  cleardevice();

  board_draw();

  spite_draw();

  EndBatchDraw();
}

void copy_cell(int x, int y) {
  int bx = spite_get_x() + x;
  int by = spite_get_y() + y;
  board_set_cell(bx, by);
}

void scene_meger_spite() {
  spite_foreach_cell(copy_cell);
}

bool collison_left(int x, int y) {
  int bx = spite_get_x() + x;
  int by = spite_get_y() + y;
  return board_get_cell(bx - 1, by);
}

bool collison_right(int x, int y) {
  int bx = spite_get_x() + x;
  int by = spite_get_y() + y;
  return board_get_cell(bx + 1, by);
}

bool collison_bottom(int x, int y) {
  int bx = spite_get_x() + x;
  int by = spite_get_y() + y;
  return board_get_cell(bx, by + 1);
}

void scene_move_spite_left() {
  if (spite_some_cell(collison_left))
    return;

  // 若无碰撞可能，移动
  spite_move_left();
}

void scene_move_spite_right() {
  if (spite_some_cell(collison_right))
    return;

  spite_move_right();
}

bool collison(int x, int y) {
  int bx = spite_get_x() + x;
  int by = spite_get_y() + y;
  return board_get_cell(bx, by);
}

// 旋转，应该要结合考虑面板是否旋转之后跟面板元素碰撞
void scene_rotate_spite() {
  int id, subid;
  spite_get_rotate_id(&id, &subid);

  if (block_some_cell(id, subid, collison))
    return;

  spite_rotate();
}

void scene_check_clear() {
  int fullrows[20];
  board_check_clear(fullrows);
}

void scene_check_gameover() {
  if (board_check_full()) {
    board_clear();
  }
}

void scene_move_spite_down() {
  if (spite_some_cell(collison_bottom)) {
    scene_meger_spite();
    scene_check_gameover();
    scene_check_clear();
    spite_new();
    return;
  }

  spite_move_down();
}

void scene_handle_msg(ExMessage* msg) {
  if (!msg->prevdown)
    return;

  int vkcode = msg->vkcode;

  if (vkcode == VK_SPACE) {
    scene_rotate_spite();
  } else if (vkcode == VK_LEFT) {
    scene_move_spite_left();
  } else if (vkcode == VK_RIGHT) {
    scene_move_spite_right();
  } else if (vkcode == VK_UP) {
    spite_move_up();
  } else if (vkcode == VK_DOWN) {
    scene_move_spite_down();
  }
}

void scene_timerfn(void*) {
  scene_move_spite_down();
}

void scene_init() {
  spite_new();

  timer1_set_callback(scene_timerfn);
}
