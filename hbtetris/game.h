#pragma once

void game_init();

void game_start();

void game_stop();

void game_pause();

void game_resume();

void game_restart();

void game_render();

void game_handle_msg(int msg, int wparam, int lparam);