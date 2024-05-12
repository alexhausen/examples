/*
3.3
Stack of Plates: Imagine a (literal) stack of plates. If the stack gets too
high, it might topple. Therefore, in real life, we would likely start a new
stack when the previous stack exceeds some threshold. Implement a data structure
SetOfStacks that mimics this. SetOfStacks should be composed of several stacks
and should create a new stack once the previous one exceeds capacity.
SetOfStacks.push() and SetOfStacks.pop() should behave identically to a single
stack (that is, pop() should return the same values as it would if there were
just a single stack).
FOLLOW UP - SImplement a function popAt(int index) which
performs a pop operation on a specific sub-stack.
Hints:#64, #87
*/

#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
class Stack {
 public:
  void push(const T& value) { s_.push_back(value); }

  T pop() {
    if (s_.empty()) {
      throw "empty stack pop";
    }
    T value = s_.back();
    s_.pop_back();
    return value;
  }

  T& top() {
    if (s_.empty()) {
      throw "empty stack top";
    }
    return s_.back();
  }

  unsigned size() const { return s_.size(); }

  bool empty() const { return s_.size() == 0; }

 private:
  std::vector<T> s_;

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const Stack<U>& s);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& s) {
  os << "[ ";
  for (const T& v : s.s_) {
    os << v << " ";
  }
  os << "]";
  return os;
}

template <typename T, int STACK_CAPACITY>
class SetOfStacks {
 public:
  void push(const T& value) {
    if (ss.empty() || ss.top().size() == STACK_CAPACITY) {
      ss.push(Stack<int>());
    }
    ss.top().push(value);
  }

  T pop() {
    T value = ss.top().pop();
    if (ss.top().empty()) {
      ss.pop();
    }
    return value;
  }

  bool empty() const { return ss.empty(); }

 public:
  Stack<Stack<int>> ss;
};

int main() {
  SetOfStacks<int, 4> ss;
  ss.push(1);
  ss.push(2);
  ss.push(3);
  ss.push(4);
  ss.push(5);
  std::cout << ss.ss << std::endl;
  assert(5 == ss.pop());
  std::cout << ss.ss << std::endl;
  assert(4 == ss.pop());
  std::cout << ss.ss << std::endl;
  assert(3 == ss.pop());
  assert(2 == ss.pop());
  assert(1 == ss.pop());
  assert(ss.empty());
  std::cout << ss.ss << std::endl;
}
