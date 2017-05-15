// https://www.codeproject.com/Articles/1236/Timers-Tutorial

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

uint64_t freq = 0u;
uint64_t CounterStart = 0u;
uint64_t startCounter = 0u;
uint64_t counter = 0u;

void StartCounter() {
  LARGE_INTEGER li;
  QueryPerformanceFrequency(&li);
  freq = li.QuadPart / 1000;
  QueryPerformanceCounter(&li);
  CounterStart = li.QuadPart;
}

uint64_t GetCounter() {
  LARGE_INTEGER li;
  QueryPerformanceCounter(&li);
  return (li.QuadPart - CounterStart) / freq;
}

void CALLBACK TimerFuntion(void* param, BOOLEAN timerOrWaitFired) {
  (void)param;
  (void)timerOrWaitFired;
  static uint64_t callsCounter = 0;
  ++callsCounter;
  counter = GetCounter();
  int64_t diffCounter = counter - startCounter;
  int64_t expected = callsCounter * 1000;
  // in RT, diff == 0
  int64_t diff = diffCounter - expected;
  printf("%ju: Timer counter %jd \n", callsCounter, diff);
}

int main(void) {
  StartCounter();

  startCounter = GetCounter();
  counter = startCounter;
  HANDLE timerHandle;
  CreateTimerQueueTimer(&timerHandle, NULL, TimerFuntion, NULL, 1000, 1000,
                        WT_EXECUTEINTIMERTHREAD);
  while (true) {
  }
  return 0;
}
