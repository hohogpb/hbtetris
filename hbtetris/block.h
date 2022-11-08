#pragma once

typedef struct {
  int id;
  int cols;
  int rows;
  int shape[];
} block_t;

typedef struct {
  int id;
  int subs;
  block_t* blocks[];
} block_group_t;

block_t* block_random();

block_t* block_get_rotate_shape(block_t* block);

bool block_some_cell(block_t* block,
                     int dx,
                     int dy,
                     bool (*predicate)(int, int));

void block_foreach_cell(block_t* block,
                        int dx,
                        int dy,
                        void (*predicate)(int, int));

int block_get_cell(block_t* block, int x, int y);


block_t* block_get(int id);
