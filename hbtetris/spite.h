#pragma once

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

bool spite_some_cell(bool (*predicate)(int, int));

void spite_foreach_cell(void (*predicate)(int, int));

int* spite_get_rotate_shape();

int spite_get_id();
int spite_get_sub_id();

void spite_get_rotate_id(int* id, int* subid);