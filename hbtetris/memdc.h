#pragma once

#include <windows.h>

bool memdc_init(int width, int height, HWND hwnd);

void memdc_swap();

void memdc_swap(HWND dstwnd);

void memdc_swap_dc(HDC dsthdc);

void memdc_setpixel(int x, int y, int color);

void memdc_rectangle(int x, int y, int right, int bottom);

void memdc_fillrectangle(int x, int y, int right, int bottom);

void memdc_setlinecolor(int color);

void memdc_setfillcolor(int color);

void memdc_setbkcolor(int color);

void memdc_cleardevice();

void memdc_drawtext(const TCHAR* str, int x, int y);
