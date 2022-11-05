#include "timer.h"

static LONGLONG _freq = 0;

bool timer_init(timer_t* timer,
                LONGLONG counter,
                double seconds,
                void (*callback)(void*),
                void* meta) {
  if (!timer)
    return false;

  timer->counter = counter;
  timer->seconds = seconds;
  timer->callback = callback;
  timer->meta = meta;
  return true;
}

void timer_advanced(timer_t* timer) {
  if (_freq == 0)
    QueryPerformanceFrequency((LARGE_INTEGER*)&_freq);

  LONGLONG counter;
  QueryPerformanceCounter((LARGE_INTEGER*)&counter);

  double seconds = (double)(counter - timer->counter) / (double)_freq;

  if (seconds < timer->seconds)
    return;

  if (timer->callback)
    timer->callback(timer->meta);

  timer->counter = counter;
}

timer_t timer1;

bool timer1_init(double seconds, void (*callback)(void*)) {
  return timer_init(&timer1, 0, seconds, callback);
}

void timer1_advanced() {
  timer_advanced(&timer1);
}

void timer1_set_callback(void (*callback)(void*)) {
  timer1.callback = callback;
}

// cur_brick = generate_brick();

// timer_init(&timer1, 0, 0.2, updatescene, scene)

// timer_step(&timer1);