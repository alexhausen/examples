/*
8.13
Stack of Boxes: You have a n boxes, with widths w_i, heights h_i, and depths
d_i. The boxes cannot be rotated and can only be stacked on top of one another
if each box in the stack is strictly larger than the box above it in width,
height, and depth. Implement a method to compute the height of the tallest
possible stack. The height of a stack is the sum of the heights of each box.
Hints:#155, #194, #214, #260, #322, #368, #378
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct box_t {
  int w;
  int h;
  int d;
  box_t(int w, int h, int d) : w{w}, h{h}, d{d} {}
};

bool operator <(const box_t& b1, const box_t& b2) {
  return b1.w < b2.w && b1.h < b2.h && b1.d < b2.d;
}

int tallest_stack_(const vector<box_t>& boxes, unsigned bottom_index, vector<int>& stack_memo) {
  if (stack_memo[bottom_index] > 0) {
    return stack_memo[bottom_index];
  }
  const box_t& bottom_box = boxes[bottom_index];
  int maxH = 0;
  for (unsigned i = bottom_index + 1; i < boxes.size(); ++i) {
    const box_t& box_i = boxes[i];
    if (box_i < bottom_box) {
      int h = tallest_stack_(boxes, i, stack_memo);
      maxH = max(h, maxH);
    }
  }
  maxH += bottom_box.h;
  stack_memo[bottom_index] = maxH;
  return maxH;
}

int tallest_stack(vector<box_t> boxes) {
  // sort larger to smaller, in one dimention
  sort(boxes.begin(), boxes.end(), [](const auto& a, const auto& b) { return a.h > b.h; });

  vector<int> stack_memo(boxes.size(), 0);
  int maxH = 0;
  for (unsigned i = 0; i < boxes.size(); i++) {
    int h = tallest_stack_(boxes, i, stack_memo);
    maxH = max(h, maxH);
  }
  return maxH;
}

int main() {
  box_t b0{ 1, 2, 3};
  box_t b1{ 10, 20, 30 };
  box_t b2{ 10, 15, 30};
  box_t b3{ 40, 40, 40};
  assert(b0 < b1);
  assert(b0 < b2);
  assert(!(b1 < b2));
  assert(!(b2 < b1));

  vector<box_t> boxes0 { b0, b0, b0};
  assert(2 == tallest_stack(boxes0));

  vector<box_t> boxes0_3_2 {b0, b3, b2};
  assert(57 == tallest_stack(boxes0_3_2));

  vector<box_t> boxes2_1_0 {b2, b1, b0};
  assert(22 == tallest_stack(boxes2_1_0));

  vector<box_t> boxes1_2_0 {b2, b1, b0};
  assert(22 == tallest_stack(boxes1_2_0));

  vector<box_t> boxes3_2_1_0 {b3, b2, b1, b0};
  assert(62 == tallest_stack(boxes3_2_1_0));

  vector<box_t> boxes3_1_2_0 {b3, b2, b1, b0};
  assert(62 == tallest_stack(boxes3_1_2_0));

  cout << "OK" << endl;
}
