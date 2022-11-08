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

// ���ϲ�����
void play_scene_meger_spite() {
  spite_foreach_cell(+spite_get_x(), +spite_get_y(), board_fill_cell);
}

// ���� �����ƶ�
void play_scene_move_spite_left() {
  if (!spite_can_move_left())
    return;
  spite_move_left();
}

// ���������ƶ�
void play_scene_move_spite_right() {
  if (!spite_can_move_right())
    return;
  spite_move_right();
}

// ���������ƶ�
void play_scene_move_spite_down() {
  if (spite_can_move_down()) {
    spite_move_down();
    return;
  }

  play_scene_spite_collision_handle();
}

// ��������
void play_scene_fall_spite() {
  while (spite_can_move_down()) {
    spite_move_down();
  }

  play_scene_spite_collision_handle();
}

// ��ʱ���������������ƶ�
void play_scene_timerfn(void*) {
  play_scene_move_spite_down();
}

// ������ת
void play_scene_rotate_spite() {
  if (!spite_can_rotate())
    return;
  spite_rotate();
}

void play_scene_check_clear() {
  int fullrows[20] = {0};  // << �����Ƿ��Ƕ�̬����,
  int fullrow_count = board_get_full_rows(fullrows);
  if (fullrow_count <= 0) {
    return;
  }

  // ��������
  audio_play_clear();

  // ��˸��ǰ������У�
  // ���ػ�������������ķ���
  // �Ƿ��� BlockInput
  board_draw_all_cells();
  board_blink_rows(fullrows, fullrow_count);

  // ���ӷ���
  score_increace_by_rows(fullrow_count);

  // ɾ����
  board_check_clear(fullrows);
}

void play_scene_check_gameover() {
  if (board_check_full()) {
    //board_clear();
    board_gameover_animation();
    game_stop();
  }
}

// ���鵽�״���
void play_scene_spite_collision_handle() {
  play_scene_meger_spite();

  play_scene_check_gameover();

  play_scene_check_clear();

  spite_new();

  speed_update();
}

// ��������
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

