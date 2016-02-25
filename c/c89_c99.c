#include <stdio.h>

enum {a, b};
int different(void) {
  printf("a=%d, b=%d\n", a, b);
  if (sizeof(enum {b, a}) != sizeof(int)) {
    return a; /* a == 1 */
  }
  printf("a=%d, b=%d\n", a, b);
  return b; /* b == 0 in C89, b == 1 in C99 */
}

int main() {
  printf("%d\n", different());
  return 0;
}
