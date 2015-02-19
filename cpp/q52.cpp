#include <iostream>

class A;

class B {
  B() { std::cout << "B"; }

public:
  friend B A::createB();
};

class A {
public:
  A() { std::cout << "A"; }

  B createB() { return B(); }
};

int main() {
  A a;
  B b = a.createB();
}

