#include "scene_stop.h"
#include "memdc.h"

void stop_scene_render();
void stop_scene_handle_msg(int msg, int wparam, int lparam);

scene_t stop_scene = {.render = stop_scene_render,
                      .handle_msg = stop_scene_handle_msg};

scene_t* stop_scene_get() {
  return &stop_scene;
}

void stop_scene_render() {
}

void stop_scene_handle_msg(int msg, int wparam, int lparam) {

}
