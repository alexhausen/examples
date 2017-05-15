#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

unsigned FlipBit(unsigned word, uint8_t bit) {
  return word ^ (1u << bit);
}

unsigned SetBit(unsigned word, uint8_t bit) {
  return word | (1u << bit);
}

unsigned ClearBit(unsigned word, uint8_t bit) {
  return word & ~(1u << bit);
}

bool CheckBit(unsigned word, uint8_t bit) {
  return ((word >> bit) & 1u ) == 1u;
}

unsigned SetNthBitToX(unsigned word, uint8_t n, bool bit_x) {
  unsigned x = (unsigned) bit_x;
  return word & (~(1u << n) | (x << n));
}

int main(void) {
  assert(FlipBit(0, 0) == 1);
  assert(FlipBit(1, 0) == 0);
  assert(FlipBit(0, 1) == 2);
  assert(FlipBit(1, 1) == 3);
  assert(FlipBit(0xFF, 0) == 0xFE);
  assert(FlipBit(0xFF, 7) == 0x7F);
  assert(FlipBit(0xFF, 1) == 0xFD);
  assert(FlipBit(0x83, 7) == 3);
}
