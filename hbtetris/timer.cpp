#include "timer.h"

static LONGLONG _freq = 0;

bool timer_init(timer_t* timer,
                LONGLONG counter,
                double seconds,
                void (*callback)(void*),
                void* meta,
                bool disable) {
  if (!timer)
    return false;

  timer->counter = counter;
  timer->seconds = seconds;
  timer->callback = callback;
  timer->meta = meta;
  timer->disable = disable;
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

  if (timer->callback && !timer->disable)
    timer->callback(timer->meta);

  timer->counter = counter;
}

void timer_enable(timer_t* timer) {
  timer->disable = false;
}

void timer_disable(timer_t* timer) {
  timer->disable = true;
}

void timer_set_interval(timer_t* timer, double secs) {
  timer->seconds = secs;
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

void timer1_enable() {
  timer_enable(&timer1);
}

void timer1_disable() {
  timer_disable(&timer1);
}

void timer1_set_interval(double secs) {
  timer_set_interval(&timer1, secs);
}
