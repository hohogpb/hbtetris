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
  lcd_font = ::CreateFont(30, 0,  //�߶�20, ��ȡ0��ʾ��ϵͳѡ�����ֵ
                          0, 0,       //�ı���б����������б��Ϊ0
                          FW_NORMAL,  //����
                          0, 0, 0,    //��б�壬���»��ߣ����л���
                          DEFAULT_CHARSET,  //�ַ���
                          OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                          DEFAULT_QUALITY,  //һϵ�е�Ĭ��ֵ
                          DEFAULT_PITCH | FF_DONTCARE,
                          L"Digital Dismay"  //��������
  );

  text_font = ::CreateFont(14, 0,  //�߶�20, ��ȡ0��ʾ��ϵͳѡ�����ֵ
                           0, 0,       //�ı���б����������б��Ϊ0
                           FW_NORMAL,  //����
                           0, 0, 0,    //��б�壬���»��ߣ����л���
                           DEFAULT_CHARSET,  //�ַ���
                           OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                           DEFAULT_QUALITY,  //һϵ�е�Ĭ��ֵ
                           DEFAULT_PITCH | FF_DONTCARE,
                           L"Arial"  //��������
  );
}
