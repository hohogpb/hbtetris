#pragma once

void board_draw();

int board_get_rows();
int board_get_cols();

int board_get_cell(int x, int y);

int board_set_cell(int x, int y, int v = 1);

void board_check_clear(int* full_rows);

bool board_check_full();

void board_clear();

void board_draw_cell(int col, int row, int color);

int board_get_full_rows(int* full_rows);

void board_blink_rows(int* rows, int count);

void board_fill_cell(int x, int y);

bool board_collison(int x, int y);

void board_draw_base();

void board_draw_valid_cells();

void board_draw_all_cells();

void board_draw_cell_clip(int col, int row, int color);

void board_gameover_animation();
