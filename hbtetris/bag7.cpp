#include "bag7.h"
#include <stdlib.h>

char bag[] = {
    'I', //'J', 'L', 
    'O', // 'S', 'T', 'Z',  // 常规
    //'X', 
    'A'                            // 自定义
};

int cursor = 0;

/**
 * 随机排序列表
 *  [0] [1] [2] [3] [4] [5] [6]
 *
 * 算法：
 *  随机-范围0~6 得到的索引跟6置换
 *  随机-范围0~5 得到的索引跟5置换
 *  随机-范围0~4 得到的索引跟4置换
 *  随机-范围0~3 得到的索引跟3置换
 *  随机-范围0~2 得到的索引跟2置换
 *  随机-范围0~1 得到的索引跟1置换
 *  此时剩余的只有一个，算法结束
 *
 * 写完才知道这叫做 shuffle（洗牌）算法，
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
