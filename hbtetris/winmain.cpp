#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <tchar.h>
#include <time.h>
#include <windows.h>
#include "game.h"
#include "memdc.h"
#include "resource.h"
#include "scene.h"
#include "timer.h"

TCHAR szTitle[100] = _T("俄罗斯方块");

TCHAR szWindowClass[100] = _T("HBTETRIS.WND");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int wWinMain(HINSTANCE hInstance,
             HINSTANCE hPrevInstance,
             LPTSTR lpCmdLine,
             int nCmdShow) {
  // 注册窗口类
  WNDCLASSEX wcex = {0};
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU_MAIN);
  wcex.lpszClassName = szWindowClass;
  RegisterClassEx(&wcex);

  int width = 600;
  int height = 600;

  // 创建窗口
  HWND hWnd = CreateWindow(szWindowClass, szTitle,
                           WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
                           CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr,
                           nullptr, hInstance, nullptr);
  if (!hWnd) {
    return -1;
  }

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  // 初始化
  srand(time(0));
  memdc_init(width, height, hWnd);
  timer1_init(1, 0);

  game_init();

  int done = false;

  // 消息循环
  while (!done) {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);

      if (msg.message == WM_QUIT) {
        done = true;
        break;
      }
    }

    timer1_advanced();

    game_render();
  }

  return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam) {
  if (message == WM_PAINT) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    memdc_swap_dc(hdc);
    EndPaint(hWnd, &ps);

  } else if (message == WM_DESTROY) {
    PostQuitMessage(0);

  } else if (message == WM_KEYDOWN) {
    game_handle_msg(message, wParam, lParam);
    // scene_handle_msg(message, wParam, lParam);
  } else if (message == WM_COMMAND) {
    int cmd = LOWORD(wParam);
    switch (cmd) {
      case ID_START:
        game_start();
        break;
      case ID_STOP:
        game_stop();
        break;
      case ID_RESTART:
        game_restart();
        break;
      case ID_PAUSE:
        game_pause();
        break;
      case ID_RESUME:
        game_resume();
        break;
      case ID_EXIT:
        DestroyWindow(hWnd);
        break;
      default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
  } else {
    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}
