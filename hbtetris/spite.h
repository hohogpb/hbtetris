#pragma once

#include "block.h"

void spite_new();

void spite_draw();

void spite_rotate();

void spite_move_left();

void spite_move_right();

void spite_move_up();

void spite_move_down();

int spite_get_cell(int x, int y);

int spite_get_x();
int spite_get_y();

block_t* spite_get_rotate_shape();

bool spite_some_cell(int dx, int dy, bool (*predicate)(int, int));

void spite_foreach_cell(int dx, int dy, void (*predicate)(int, int));

bool spite_can_move_left();
bool spite_can_move_right();
bool spite_can_move_down();
bool spite_can_rotate();