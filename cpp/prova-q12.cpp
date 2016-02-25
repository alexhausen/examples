#include <iostream>

class Base {
public:
  Base() {
    std::cout << "Base::Constructor" << std::endl;
  }

  virtual ~Base() {
    std::cout << "Base::Destructor" << std::endl;
  }

  virtual void f() = 0;

};

class Derived : public Base {
public:
    Derived() {
        std::cout << "Derived::Constructor" << std::endl;
    }

    virtual ~Derived() {
        std::cout << "Derived::Destructor" << std::endl;
    }

    void f() {
        std::cout << "Derived::f" << std::endl;
    }
};

int main() {
    Base* p = new Derived();
    p->f();
    delete p;
    return 0;
}
