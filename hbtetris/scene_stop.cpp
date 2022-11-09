#include "scene_stop.h"
#include "fonts.h"
#include "game.h"
#include "memdc.h"

void stop_scene_render();
void stop_scene_handle_msg(int msg, int wparam, int lparam);

scene_t stop_scene = {.render = stop_scene_render,
                      .handle_msg = stop_scene_handle_msg};

scene_t* stop_scene_get() {
  return &stop_scene;
}

void stop_scene_render() {
  int x = 30;
  int y = 200 - 20;
  int width = 170;
  int height = 40;

  // 绘制外侧边框
  memdc_setlinecolor(RGB(114, 128, 92));
  memdc_rectangle(x, y, x + width, y + height);

  memdc_setfont(fonts_get_text_font());
  memdc_drawtext(L"按任意键开始", x, y, width, height,
                 DT_VCENTER | DT_CENTER | DT_SINGLELINE);
}

void stop_scene_handle_msg(int msg, int wparam, int lparam) {
  game_restart();
}
