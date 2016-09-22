#include "fun.h"
#include <stdio.h>
#include <string.h>

int fun(const char* str) {
  int out;
  int r = dep(strlen(str), &out);
  return 2 * out + r;
}

int dep(int in, int* out) {
  puts("real dep");
  *out = in + 1000;
  return in;
}

