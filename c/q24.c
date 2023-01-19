#include <stdio.h>

struct pp {
  int x;
  int y;
};

int main() {
  struct pp p1[] = {1,2,3,4,5,6};
  struct pp *ptr1 = p1;
  printf("%d %d\n", ptr1->x, (ptr1+2)->x);
}
