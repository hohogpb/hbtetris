#pragma once

#include <Windows.h>

typedef struct {
  LONGLONG counter;
  double seconds;
  void (*callback)(void*);
  void* meta;
} timer_t;

bool timer_init(timer_t* timer,
                LONGLONG counter,
                double seconds,
                void (*callback)(void*),
                void* meta = 0);

void timer_advanced(timer_t* timer);




bool timer1_init(double seconds, void (*callback)(void*));

void timer1_advanced();

void timer1_set_callback(void (*callback)(void*));
