#include "game.h"
#include "board.h"
#include "config.h"
#include "memdc.h"
#include "scene.h"
#include "scene_play.h"
#include "scene_stop.h"
#include "score.h"
#include "spite.h"
#include "timer.h"
#include "speed.h"

enum { GAME_PLAYING, GAME_PAUSE, GAME_STOPED };

bool game_state = GAME_STOPED;

scene_t* scene;

void game_init() {
  scene = stop_scene_get();

  speed_inc();
}

void game_start() {
  scene = play_scene_get();
  play_scene_init();
}

void game_stop() {
  if (scene == play_scene_get()) {
    play_scene_stop();
  }
  scene = stop_scene_get();
}

void game_pause() {
  if (scene == play_scene_get()) {
    play_scene_pause();
  }
}

void game_resume() {
  if (scene == play_scene_get()) {
    play_scene_resume();
  }
}

void game_restart() {
  scene = play_scene_get();
  play_scene_init();
}

void game_render() {
  memdc_setbkcolor(bk_color);
  memdc_cleardevice();

  board_draw_base();

  if (scene) {
    scene->render();
  }

  memdc_swap();
}

void game_handle_msg(int msg, int wparam, int lparam) {
  if (scene) {
    scene->handle_msg(msg, wparam, lparam);
  }
}
