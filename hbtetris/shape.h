#pragma once

typedef struct {
  int id;         // 形状标识
  int subs;       // 子形状
  int* shapes[];  // 子形状数据数组
} block_t;

int* block_get_shape(int id, int subid);

int block_get_rotate_shape(int id, int subid);

block_t* block_get(int id);

block_t* block_random();

bool block_some_cell(int id, int subid, bool (*predicate)(int, int));