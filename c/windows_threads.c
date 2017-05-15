#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

uint64_t freq = 0u;
uint64_t CounterStart = 0u;

void StartCounter() {
  LARGE_INTEGER li;
  QueryPerformanceFrequency(&li);
  freq = li.QuadPart / 1000000;
  QueryPerformanceCounter(&li);
  CounterStart = li.QuadPart;
}

uint64_t GetCounter() {
  LARGE_INTEGER li;
  QueryPerformanceCounter(&li);
  return (li.QuadPart - CounterStart) / freq;
}

DWORD WINAPI ThreadFunction(LPVOID param) {
  (void)param;
  StartCounter();
  uint64_t startCounter = GetCounter();
  uint64_t loop = 0u;
  // 20 ms 'timer' (sic) loop
  while (true) {
    int64_t diffCounter = GetCounter() - startCounter;
    int64_t expected = loop * 20000;
    int64_t diff = diffCounter - expected;
    if (diff < 20000) continue;
    if (diff > 21000)
      printf("%ju: Timer delay %f ms \n", loop, (diff - 20000) / 1000.0);
    ++loop;
  }
  return 0;
}

int main(void) {
  DWORD thread_id;
  HANDLE threadHandle =
      CreateThread(NULL, 0, ThreadFunction, NULL, 0, &thread_id);
  assert(threadHandle);

  BOOL prioritySetProcess =
      SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
  assert(prioritySetProcess);

  BOOL prioritySetThread =
      SetThreadPriority(threadHandle, THREAD_PRIORITY_HIGHEST);
  assert(prioritySetThread);

  while (true) {
    Sleep(1);
  }

  WaitForSingleObject(threadHandle, INFINITE);
  CloseHandle(threadHandle);
  return 0;
}