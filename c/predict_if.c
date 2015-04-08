//http://nullonerror.org/2015/03/31/o-if-mais-rapido-do-velho-oeste/

#include <stdio.h>

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

int main(int argc, char** argv) {
  if (likely(argc == 1)) {
    puts("ok");
  } else {
    puts("ok too, but less likely.");
  }
}
