// eluosifangkuai.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <graphics.h>
#include <inttypes.h>
#include <stdio.h>
#include <iostream>
#include "scene.h"
#include "timer.h"

int main() {
  srand(time(0));

  initgraph(640, 480, EX_SHOWCONSOLE);

  timer1_init(0.2, nullptr);

  scene_init();

  while (true) {
    ExMessage msg;
    if (peekmessage(&msg, EX_KEY)) {
      scene_handle_msg(&msg);
    }

    timer1_advanced();

    scene_draw();
  }

  return 0;
}
