/*
Sort Stack: Write a program to sort a stack such that the smallest items are on the top. You can use
an additional temporary stack, but you may not copy the elements into any other data structure
(such as an array). The stack supports the following operations: push, pop, peek, and is Empty.
Hints:# 15, #32, #43
*/

#include <cassert>
#include <iostream>
#include <stack>

// This class pushes a value into a sorted "stack";
// greater to lower values
class SortedStack {
 public:
  void push(int value) {
    if (s_.empty()) {
      s_.push(value);
      return;
    }
    std::stack<int> temp;
    while (!s_.empty() && value < s_.top()) {
      temp.push(s_.top());
      s_.pop();
    }
    s_.push(value);
    while (!temp.empty()) {
      s_.push(temp.top());
      temp.pop();
    }
  }

  int pop() {
    if (s_.empty()) {
      throw "pop from empty stack";
    }
    int v = s_.top();
    s_.pop();
    return v;
  }

  unsigned size() const {
    return s_.size();
  }
  
  bool empty() const {
    return s_.empty();
  }

 private:
  std::stack<int> s_;
};

void sort(std::stack<int>& s) {
  SortedStack r;
  while (!s.empty()) {
    auto v = s.top();
    s.pop();
    r.push(v);
  }
  while (!r.empty()) {
    s.push(r.pop());
  }
}

int main() {
  /*
  SortedStack ss;
  ss.push(5);
  ss.push(1);
  ss.push(2);
  ss.push(4);
  ss.push(3);
  ss.push(4);
  assert(6 == ss.size());
  assert(5 == ss.pop());
  assert(4 == ss.pop());
  assert(4 == ss.pop());
  assert(3 == ss.pop());
  assert(2 == ss.pop());
  assert(1 == ss.pop());
  assert(ss.empty());
  */

  std::stack<int> s;
  s.push(5);
  s.push(1);
  s.push(2);
  s.push(4);
  s.push(3);
  s.push(4);
  sort(s);
  assert(6 == s.size());
  assert(1 == s.top());
  s.pop();
  assert(2 == s.top());
  s.pop();
  assert(3 == s.top());
  s.pop();
  assert(4 == s.top());
  s.pop();
  assert(4 == s.top());
  s.pop();
  assert(5 == s.top());
  s.pop();
  assert(s.empty());

  std::cout << "OK" << std::endl;
}
