#include "bag7.h"
#include <stdlib.h>

char bag[] = {
    'I', //'J', 'L', 
    'O', // 'S', 'T', 'Z',  // ����
    //'X', 
    'A'                            // �Զ���
};

int cursor = 0;

/**
 * ��������б�
 *  [0] [1] [2] [3] [4] [5] [6]
 *
 * �㷨��
 *  ���-��Χ0~6 �õ���������6�û�
 *  ���-��Χ0~5 �õ���������5�û�
 *  ���-��Χ0~4 �õ���������4�û�
 *  ���-��Χ0~3 �õ���������3�û�
 *  ���-��Χ0~2 �õ���������2�û�
 *  ���-��Χ0~1 �õ���������1�û�
 *  ��ʱʣ���ֻ��һ�����㷨����
 *
 * д���֪������� shuffle��ϴ�ƣ��㷨��
 */
void bag7_regenerate() {
  for (int i = sizeof(bag); i > 0; i--) {
    int j = rand() % i;
    // swap bag[i] bag[j]
    char tmp = bag[i - 1];
    bag[i - 1] = bag[j];
    bag[j] = tmp;
  }
  cursor = 0;
}

int bag7_pick() {
  int id = bag[cursor];
  cursor++;

  if (cursor >= sizeof(bag)) {
    bag7_regenerate();
    cursor = 0;
  }
  return id;
}

int bag7_next() {
  int id = bag[cursor];
  return id;
}

void bag7_init() {
  bag7_regenerate();
}
