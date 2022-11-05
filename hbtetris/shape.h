#pragma once

typedef struct {
  int id;         // ��״��ʶ
  int subs;       // ����״
  int* shapes[];  // ����״��������
} block_t;

int* block_get_shape(int id, int subid);

int block_get_rotate_shape(int id, int subid);

block_t* block_get(int id);

block_t* block_random();

bool block_some_cell(int id, int subid, bool (*predicate)(int, int));