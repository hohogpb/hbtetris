#include "memdc.h"
#include <tchar.h>

typedef struct {
  int width;
  int height;
  HDC hdc;
  HBITMAP bitmap;
  int linecolor;
  int fillcolor;
  int bkcolor;
  int textcolor;
  int bkmode;
  HWND hwnd;
  HFONT hfont;
} memdc_t;

bool memdc_init(memdc_t* dc, int width, int height, HWND hwnd) {
  BITMAPINFO bmp_info = {0};
  bmp_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmp_info.bmiHeader.biWidth = width;
  bmp_info.bmiHeader.biHeight = -height;
  bmp_info.bmiHeader.biPlanes = 1;
  bmp_info.bmiHeader.biBitCount = 32;

  int pixel_num = width * height;
  int pixel_bytes = pixel_num * 4;

  HDC null_hdc = ::CreateCompatibleDC(NULL);

  COLORREF* pixels = NULL;
  HBITMAP bitmap = ::CreateDIBSection(null_hdc, (BITMAPINFO*)&bmp_info,
                                      DIB_RGB_COLORS, (void**)&pixels, NULL, 0);
  if (!bitmap)
    return false;

  ::SelectObject(null_hdc, bitmap);

  dc->width = width;
  dc->height = height;
  dc->hdc = null_hdc;
  dc->bitmap = bitmap;
  dc->hwnd = hwnd;
  dc->hfont = 0;

  return true;
}

void memdc_destory(memdc_t* dc) {
  if (dc->bitmap) {
    ::DeleteObject(dc->bitmap);
    dc->bitmap = NULL;
  }

  if (dc->hdc) {
    ::DeleteObject(dc->hdc);
    dc->hdc = NULL;
  }
}

void memdc_bitblt(memdc_t* dc, HWND dstwnd) {
  HDC hdc = ::GetDC(dstwnd);
  ::BitBlt(hdc, 0, 0, dc->width, dc->height, dc->hdc, 0, 0, SRCCOPY);
  ::ReleaseDC(dstwnd, hdc);
}

void memdc_bitblt_dc(memdc_t* dc, HDC dsthdc) {
  ::BitBlt(dsthdc, 0, 0, dc->width, dc->height, dc->hdc, 0, 0, SRCCOPY);
}

memdc_t memdc;

bool memdc_init(int width, int height, HWND hwnd) {
  return memdc_init(&memdc, width, height, hwnd);
}

void memdc_swap() {
  if (memdc.hwnd)
    memdc_bitblt(&memdc, memdc.hwnd);
}

void memdc_swap(HWND dstwnd) {
  memdc_bitblt(&memdc, dstwnd);
}

void memdc_swap_dc(HDC dsthdc) {
  memdc_bitblt_dc(&memdc, dsthdc);
}

void memdc_setpixel(int x, int y, int color) {
  ::SetPixel(memdc.hdc, x, y, color);
}

void memdc_rectangle(int x, int y, int right, int bottom) {
  RECT rect = {x, y, right, bottom};

  HPEN line_pen = ::CreatePen(PS_SOLID, 1, memdc.linecolor);
  HGDIOBJ old_pen = ::SelectObject(memdc.hdc, line_pen);

  HBRUSH fill_brush = ::CreateSolidBrush(memdc.bkcolor);
  HGDIOBJ old_brush = ::SelectObject(memdc.hdc, fill_brush);

  ::Rectangle(memdc.hdc, x, y, right, bottom);

  ::SelectObject(memdc.hdc, old_brush);
  ::SelectObject(memdc.hdc, old_pen);

  ::DeleteObject(line_pen);
  ::DeleteObject(fill_brush);
}

void memdc_fillrectangle(int x, int y, int right, int bottom) {
  RECT rect = {x, y, right, bottom};

  HBRUSH brush = ::CreateSolidBrush(memdc.fillcolor);
  ::FillRect(memdc.hdc, &rect, brush);
  ::DeleteObject(brush);
}

int memdc_settextcolor(int color) {
  int old_textcolor = ::GetTextColor(memdc.hdc);
  ::SetTextColor(memdc.hdc, color);
  memdc.textcolor = color;
  return old_textcolor;
}

void memdc_setlinecolor(int color) {
  memdc.linecolor = color;
}

void memdc_setfillcolor(int color) {
  memdc.fillcolor = color;
}

void memdc_setbkcolor(int color) {
  memdc.bkcolor = color;
  ::SetBkColor(memdc.hdc, color);
}

void memdc_cleardevice() {
  RECT rect = {0, 0, memdc.width, memdc.height};

  HBRUSH brush = ::CreateSolidBrush(memdc.bkcolor);
  ::FillRect(memdc.hdc, &rect, brush);
  ::DeleteObject(brush);
}

HFONT memdc_setfont(HFONT hfont) {
  if (!hfont)
    return memdc.hfont;

  HFONT holdfont = (HFONT)SelectObject(memdc.hdc, hfont);
  memdc.hfont = hfont;

  return holdfont;
}

void memdc_textout(const TCHAR* str, int x, int y) {
  int len = _tcslen(str);
  ::TextOut(memdc.hdc, x, y, str, len);
}

int memdc_setbkmode(int mode) {
  int old_mode = ::SetBkMode(memdc.hdc, mode);
  memdc.bkmode = mode;
  return old_mode;
}

void memdc_drawtext(const TCHAR* str,
                    int x,
                    int y,
                    int width,
                    int height,
                    int format) {
  int len = _tcslen(str);

  RECT rect = {x, y, x + width, y + height};

  ::DrawText(memdc.hdc, str, len, &rect, format);
}
