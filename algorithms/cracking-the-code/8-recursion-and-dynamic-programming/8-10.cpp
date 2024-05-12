/*
8.1 O
Paint Fill: Implement the "paint fill" function that one might see on many image 
editing programs.
That is, given a screen (represented by a two-dimensional array of colors), a 
point, and a new color, fill in the surrounding area until the color changes 
from the original color.
Hints: #364, #382
*/

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using u32 = u_int32_t;

void paint_fill2(vector<vector<int>>& screen, int row, int col, int new_color, int original_color) {
  if (row < 0 || col < 0) {
    return;
  }
  int last_row = static_cast<int>(screen.size()) - 1;
  int last_col = static_cast<int>(screen[0].size()) - 1;
  if (row > last_row || col > last_col) {
    return;
  }
  if (screen[row][col] != original_color) {
    return;
  }
  screen[row][col] = new_color;
  paint_fill2(screen, row-1, col, new_color, original_color);
  paint_fill2(screen, row, col-1, new_color, original_color);
  paint_fill2(screen, row, col+1, new_color, original_color);
  paint_fill2(screen, row+1, col, new_color, original_color);
}

void paint_fill(vector<vector<int>>& screen, int row, int col, int new_color) {
  int original_color = screen[row][col];
  paint_fill2(screen, row, col, new_color, original_color);
}

int main() {
  int new_color = 9;

  vector<vector<int>> screen1 = {
    { 0, 1, 1 },
    { 0, 1, 0 },
    { 0, 0, 1 },
  };
  vector<vector<int>> expected1 = {
    { 0, 9, 9 },
    { 0, 9, 0 },
    { 0, 0, 1 },
  };
  paint_fill(screen1, 1, 1, new_color);
  assert(screen1 == expected1);

  vector<vector<int>> screen2 = {
    { 0, 1, 0 },
    { 0, 1, 0 },
    { 0, 0, 0 },
  };
  vector<vector<int>> expected2 = {
    { 9, 1, 9 },
    { 9, 1, 9 },
    { 9, 9, 9 },
  };
  paint_fill(screen2, 2, 0, new_color);
  assert(screen2 == expected2);

  cout << "OK" << endl;
}
