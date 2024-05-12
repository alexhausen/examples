/*
8.6
Towers of Hanoi: In the classic problem of the Towers of Hanoi, you have 3
towers and N disks of different sizes which can slide onto any tower. The puzzle
starts with disks sorted in ascending order of size from top to bottom (i.e.,
each disk sits on top of an even larger one). You have the following
constraints:
(1) Only one disk can be moved at a time.
(2) A disk is slid off the top of one tower onto another tower.
(3) A disk cannot be placed on top of a smaller disk.
Write a program to move the disks from the first tower to the last using stacks.
Hints: #144, #224, #250, #272, #318
*/

#include <cassert>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct Tower {
  Tower(const string& name) : name_{name} {}

  void push(int x) { s_.push(x); }

  int pop() {
    int x = s_.top();
    s_.pop();
    return x;
  }

  bool empty() const { return s_.empty(); }

  int size() const { return s_.size(); }

  void print() {
    cout << " " << name_ << ": { ";
    stack<int> temp;
    while (!s_.empty()) {
      int x = s_.top();
      cout << x << " ";
      temp.push(x);
      s_.pop();
    }
    while (!temp.empty()) {
      s_.push(temp.top());
      temp.pop();
    }
    cout << "}\n";
  };

 private:
  stack<int> s_;
  std::string name_;
};

void print_towers(Tower& a, Tower& b, Tower& c) {
  a.print();
  b.print();
  c.print();
  cout << " ===========" << endl;
}

void hanoi_(int n, Tower& src, Tower& dst, Tower& temp) {
  if (n == 0) return;

  hanoi_(n - 1, src, temp, dst);

  // move src -> dst
  dst.push(src.pop());
  print_towers(src, temp, dst);

  hanoi_(n - 1, temp, dst, src);
}

void hanoi(Tower& src, Tower& dst) {
  Tower temp("temp");
  return hanoi_(src.size(), src, dst, temp);
}

int main() {
  Tower src("src");
  src.push(4);
  src.push(3);
  src.push(2);
  src.push(1);
  Tower dst("dst");
  hanoi(src, dst);

  assert(src.empty());
  assert(dst.pop() == 1);
  assert(dst.pop() == 2);
  assert(dst.pop() == 3);
  assert(dst.pop() == 4);

  cout << "OK" << endl;
}
