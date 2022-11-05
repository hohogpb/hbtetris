#pragma once

void board_draw();

int board_get_cell(int x, int y);

int board_set_cell(int x, int y, int v = 1);

void board_check_clear(int* full_rows);

bool board_check_full();

void board_clear();