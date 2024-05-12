/*
5.8
Draw Line: A monochrome screen is stored as a single array of bytes, allowing 
eight consecutive pixels to be stored in one byte. The screen has width w, where 
w is divisible by 8 (that is, no byte will be split across rows). The height of 
the screen, of course, can be derived from the length of the array and the width. 
Implement a function that draws a horizontal line from (x1, y) to (x2, y).
The method signature should look something like:
drawline(byte[] screen, int width, int x1, int x2, int y)
Hints: #366, #381, #384, #391
*/

#include <cassert>
#include <iostream>

void drawline(u_int8_t screen[], int width, int x1, int x2, int y) {
  // int height = len * 8 / width;
  /*
  // naive solution:
  for (int x = x1; x <= x2; x++) {
    int i = width * 8 + x;
    set_bit(screen, i);
  }
  */
  int start_offset = x1 % 8;
  int first_full_byte = x1 / 8;
  if (start_offset != 0) first_full_byte++;

  int end_offset = x2 % 8;
  int last_full_byte = x2 / 8;
  if (end_offset != 7) last_full_byte--;

  int screen_line = width / 8 * y;

  // set full bytes in the middle
  for (int offset = first_full_byte; offset <= last_full_byte; offset++) {
    int i = screen_line + offset;
    screen[i] = 0xFFu;
  }

  u_int8_t start_mask = 0xFFu >> start_offset;
  u_int8_t end_mask = ~(0xFFu >> (end_offset + 1));
  if (x1 / 8 == x2 / 8) {
    u_int8_t mask = start_mask & end_mask; // masks intersection
    screen[screen_line + (x1 / 8)] |= mask;
  } else {
    if (start_offset != 0) {
      //set first part bits
      int i = screen_line + first_full_byte - 1;
      screen[i] |= start_mask;
    }
    if (end_offset != 7) {
      //set last part bits
      int i = screen_line + last_full_byte + 1;
      screen[i] |= end_mask;
    }
  }
}

int main() {
  u_int8_t screen1[] = { 0, 0, 0, 0 };
  drawline(screen1, 8, 2, 4, 1);
  assert(screen1[0] == 0);
  assert(screen1[1] == 0x38u);
  assert(screen1[2] == 0);
  assert(screen1[3] == 0);

  u_int8_t screen2[] = { 0, 0, 0, 0 };
  drawline(screen2, 8, 0, 7, 2);
  assert(screen2[0] == 0);
  assert(screen2[1] == 0);
  assert(screen2[2] == 0xFFu);
  assert(screen2[3] == 0);

  std::cout << "OK" << std::endl;
}
