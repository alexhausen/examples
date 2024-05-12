/*
3.4
Queue via Stacks: Implement a MyQueue class which implements a queue using two
stacks.
Hints: #98, #114
*/

#include <cassert>
#include <stack>
#include <iostream>

class MyQueue {
 public:
  void push(int v) {
    s_new.push(v);
  }

  int pop() {
    if (s_old.empty()) {
      // pop from s_new into s_old
      while (!s_new.empty()) {
        s_old.push(s_new.top());
        s_new.pop();
      }
    }
    if (s_old.empty()) {
      throw "empty queue";
    }
    int v = s_old.top();
    s_old.pop();
    return v;
  }

  unsigned size() const {
    return s_new.size() + s_old.size();
  }

  bool empty() const {
    return s_new.empty() && s_old.empty();
  }

 private:
  std::stack<int> s_new; // <- push into here
  std::stack<int> s_old; // <- pop from here
};

int main() {
  MyQueue mq; 
  mq.push(1);
  mq.push(2);
  mq.push(3);
  assert(3 == mq.size());
  assert(1 == mq.pop());
  assert(2 == mq.pop());
  assert(3 == mq.pop());
  assert(mq.empty());
  std::cout << "OK" << std::endl;
}
