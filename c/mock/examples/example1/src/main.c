#include <stdio.h>
#include "fun.h"

int main() {
  int x;
  int r = fun("hello");
  printf("fun returns %d\n", r);
  return 0;
}
