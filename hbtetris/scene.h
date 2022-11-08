#pragma once

void scene_init();

void scene_draw();

void scene_handle_msg(int msg, int wparam, int lparam);

typedef struct {
  void (*render)();
  void (*handle_msg)(int msg, int wparam, int lparam);
} scene_t;
