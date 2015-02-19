#include <pthread.h>
#include <stdio.h>

void* exec(void* t)
{
 printf("Thread\n");
 return 0;
}

int runthething()
{
  pthread_t execThread;
  printf("debug1\n");
  pthread_create(&execThread, 0, exec, 0);
  printf("debug2\n");
  pthread_detach(execThread);
  printf("debug3\n");

  sleep(5);
  return 1;
}

