// clang++ -O3 -g3 -Xclang -flto-visibility-public-std ring_queue.cpp
// mingw32-g++ -O3 -g3 -std=c++14 ring_queue.cpp

#include "ring_queue.hpp"

#include <chrono>
#include <iostream>
#include <list>
#include <queue>
// #include <memory>
// #include <vector>

#include <cassert>

#define INITIAL_CONTAINER_SIZE 500'000
#define MAX_INSERTS 1'000'000

struct S {
  char str[1024];
};

void test_rb() {
  ring_queue<int> rb1;
  assert(rb1.empty());
  assert(0 == rb1.size());
  rb1.push(1);
  assert(1 == rb1.size());
  rb1.push(2);
  assert(2 == rb1.size());
  assert(1 == rb1.pop());
  assert(2 == rb1.pop());
  assert(rb1.empty());
  assert(0 == rb1.size());
  try {
    rb1.pop();
    assert(false);
  } catch (...) {
  }

  ring_queue<int> rb2{2};
  assert(rb2.empty());
  assert(0 == rb2.size());
  rb2.push(1);
  rb2.push(2);
  assert(2 == rb2.size());
  rb2.push(3);
  rb2.print();
  assert(3 == rb2.size());
  assert(1 == rb2.pop());
  assert(2 == rb2.pop());
  assert(1 == rb2.size());
  rb2.push(4);
  rb2.push(5);
  rb2.print();
  assert(3 == rb2.pop());
  assert(2 == rb2.size());
  assert(4 == rb2.pop());
  assert(1 == rb2.size());
  rb2.print();

  ring_queue<int> rb3{3};
  rb3.push(1);
  rb3.push(2);
  rb3.push(3);
  rb3.print();
  assert(1 == rb3.pop());
  rb3.print();
  rb3.push(4);
  rb3.print();
  rb3.push(5);
  rb3.print();
  assert(2 == rb3.pop());
  rb3.print();
  rb3.push(6);
  rb3.push(7);
  rb3.push(8);
  rb3.print();
  assert(3 == rb3.pop());
  rb3.push(9);
  rb3.print();
  rb3.push(10);
  rb3.print();
}

int main() {
  test_rb();

  S s{};

  // benchmark ring_queue
  ring_queue<S*> rb{INITIAL_CONTAINER_SIZE};
  auto start = std::chrono::steady_clock::now();
  for (int i = 0; i < MAX_INSERTS; ++i) {
    rb.push(&s);
  }
  for (int i = 0; i < MAX_INSERTS; ++i) {
    rb.pop();
  }
  auto end = std::chrono::steady_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                  .count();
  std::cout << "ring_queue - size: " << rb.size() << ", time: " << time << "ms"
            << std::endl;

  // benchmark deque (double-ended queue)
  std::deque<S*> deque;
  deque.resize(INITIAL_CONTAINER_SIZE);
  deque.clear();
  start = std::chrono::steady_clock::now();
  for (int i = 0; i < MAX_INSERTS; ++i) {
    deque.push_back(&s);
  }
  for (int i = 0; i < MAX_INSERTS; ++i) {
    deque.pop_front();
  }
  end = std::chrono::steady_clock::now();
  time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
             .count();
  std::cout << "deque - size: " << deque.size() << ", time: " << time << "ms"
            << std::endl;

  // benchmark queue implemented as a list
  std::queue<S*, std::list<S*>> queue_l;
  start = std::chrono::steady_clock::now();
  for (int i = 0; i < MAX_INSERTS; ++i) {
    queue_l.push(&s);
  }
  for (int i = 0; i < MAX_INSERTS; ++i) {
    queue_l.pop();
  }
  end = std::chrono::steady_clock::now();
  time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
             .count();
  std::cout << "queue (list) - size: " << queue_l.size() << ", time: " << time
            << "ms" << std::endl;

  // queue implemented as a vector doesn't compile because vector has no
  // pop_front() method
  // std::queue<S*, std::vector<S*>> queue_v;
}
