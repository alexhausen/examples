#include <stdio.h>

void f(int* array, int size) {

  //int size = sizeof(array) / sizeof(int);
  printf("%d\n", size);
}

int main() {

  int array[] = { 5, 2, 3, 1, 0, 7 };
  int size = sizeof(array) / sizeof(int);
  printf("%d\n", size);

  f(array, size);

  return 0;
}