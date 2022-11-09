#include "fonts.h"
#include <Windows.h>


HFONT lcd_font;
HFONT text_font;

HFONT fonts_get_text_font() {
  return text_font;
}

HFONT fonts_get_lcd_font() {
  return lcd_font;
}

void fonts_init() {
  lcd_font = ::CreateFont(30, 0,  //高度20, 宽取0表示由系统选择最佳值
                          0, 0,       //文本倾斜，与字体倾斜都为0
                          FW_NORMAL,  //粗体
                          0, 0, 0,    //非斜体，无下划线，无中划线
                          DEFAULT_CHARSET,  //字符集
                          OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                          DEFAULT_QUALITY,  //一系列的默认值
                          DEFAULT_PITCH | FF_DONTCARE,
                          L"Digital Dismay"  //字体名称
  );

  text_font = ::CreateFont(14, 0,  //高度20, 宽取0表示由系统选择最佳值
                           0, 0,       //文本倾斜，与字体倾斜都为0
                           FW_NORMAL,  //粗体
                           0, 0, 0,    //非斜体，无下划线，无中划线
                           DEFAULT_CHARSET,  //字符集
                           OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                           DEFAULT_QUALITY,  //一系列的默认值
                           DEFAULT_PITCH | FF_DONTCARE,
                           L"Arial"  //字体名称
  );
}
