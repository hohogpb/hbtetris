#include <stdio.h>
#include "audio.h"
#include "block.h"
#include "board.h"
#include "config.h"
#include "level.h"
#include "memdc.h"
#include "scene.h"
#include "score.h"
#include "speed.h"
#include "spite.h"
#include "spite_queue.h"
#include "timer.h"
#include "game.h"

void play_scene_render();
void play_scene_handle_msg(int msg, int wparam, int lparam);
void play_scene_timerfn(void*);
void play_scene_spite_collision_handle();

scene_t play_scene = {.render = play_scene_render,
                      .handle_msg = play_scene_handle_msg};

scene_t* play_scene_get() {
  return &play_scene;
}

// 面板合并方块
void play_scene_meger_spite() {
  spite_foreach_cell(+spite_get_x(), +spite_get_y(), board_fill_cell);
}

// 方块 向左移动
void play_scene_move_spite_left() {
  if (!spite_can_move_left())
    return;
  spite_move_left();
}

// 方块向右移动
void play_scene_move_spite_right() {
  if (!spite_can_move_right())
    return;
  spite_move_right();
}

// 方块向下移动
void play_scene_move_spite_down() {
  if (spite_can_move_down()) {
    spite_move_down();
    return;
  }

  play_scene_spite_collision_handle();
}

// 方块下落
void play_scene_fall_spite() {
  while (spite_can_move_down()) {
    spite_move_down();
  }

  play_scene_spite_collision_handle();
}

// 定时器驱动方块向下移动
void play_scene_timerfn(void*) {
  play_scene_move_spite_down();
}

// 方块旋转
void play_scene_rotate_spite() {
  if (!spite_can_rotate())
    return;
  spite_rotate();
}

void play_scene_check_clear() {
  int fullrows[20] = {0};  // << 这里是否考虑动态分配,
  int fullrow_count = board_get_full_rows(fullrows);
  if (fullrow_count <= 0) {
    return;
  }

  // 播放声音
  audio_play_clear();

  // 闪烁当前清除的行，
  // 先重绘面板以清除下落的方块
  // 是否考虑 BlockInput
  board_draw_all_cells();
  board_blink_rows(fullrows, fullrow_count);

  // 增加分数
  score_increace_by_rows(fullrow_count);

  // 删除行
  board_check_clear(fullrows);
}

void play_scene_check_gameover() {
  if (board_check_full()) {
    //board_clear();
    board_gameover_animation();
    game_stop();
  }
}

// 方块到底处理
void play_scene_spite_collision_handle() {
  play_scene_meger_spite();

  play_scene_check_gameover();

  play_scene_check_clear();

  spite_new();

  speed_update();
}

// 按键处理
void play_scene_handle_msg(int msg, int wparam, int lparam) {
  if (msg != WM_KEYDOWN)
    return;

  int vkcode = wparam;

  if (vkcode == VK_SPACE) {
    play_scene_fall_spite();

  } else if (vkcode == VK_LEFT) {
    play_scene_move_spite_left();
    audio_play_key_press();

  } else if (vkcode == VK_RIGHT) {
    play_scene_move_spite_right();
    audio_play_key_press();

  } else if (vkcode == VK_UP) {
    play_scene_rotate_spite();
    audio_play_key_press();

  } else if (vkcode == VK_DOWN) {
    play_scene_move_spite_down();
    audio_play_key_press();
  }
}

void play_scene_render() {
  board_draw_valid_cells();

  spite_draw();

  score_draw();

  level_draw();

  speed_draw();

  next_spite_draw();
}

void play_scene_init() {
  board_clear();

  spite_new();

  score_reset();

  timer1_set_callback(play_scene_timerfn);
}

void play_scene_stop() {
  timer1_set_callback(0);
  // timer1_disable();
}

void play_scene_pause() {
  timer1_set_callback(0);
}

void play_scene_resume() {
  timer1_set_callback(play_scene_timerfn);
  // enbaleinput
}

