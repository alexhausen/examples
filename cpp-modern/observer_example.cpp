/*
 Observer pattern usage example.
*/

#include <iostream>

#include "observer.hpp"

// Example observers tags
class PositiveObserver;
class NegativeObserver;
class ZeroObserver;
class ErrorObserver;

// Example observables
using OnPositive = Observable<PositiveObserver, int, float>;
using OnNegative = Observable<NegativeObserver, int, float>;
using OnZero = Observable<ZeroObserver>;
using OnError = Observable<ErrorObserver, const char*>;

// Example subject is observable
class Subject : public OnPositive,
                public OnNegative,
                public OnZero,
                public OnError {
 public:
  using OnError::attach;
  using OnNegative::attach;
  using OnPositive::attach;
  using OnZero::attach;

  void Update(int x) {
    try {
      if (x > 0) {
        OnPositive::notify(x, 0.0f);
      } else if (x < 0) {
        OnNegative::notify(-x, 100.0f);
      } else {
        OnZero::notify();
      }
    } catch (...) {
      OnError::notify("error!");
    }
  }
};

int main(void) {
  auto positive_observer1 =
      std::make_shared<std::function<void(int, float)>>([](int x, float y) {
        std::cout << "Positive " << x << " " << y << std::endl;
      });

  auto positive_observer2 =
      std::make_shared<std::function<void(int, float)>>([](int x, float y) {
        std::cout << "Another positive observer " << x << " " << y << std::endl;
      });

  auto throw_exception = std::make_shared<std::function<void(int, float)>>(
      [](int, float) { throw "this will be captured by OnError"; });

  auto negative_observer =
      std::make_shared<std::function<void(int, float)>>([](int x, float y) {
        std::cout << "Negative " << x << " " << y << std::endl;
      });

  auto zero_observer = std::make_shared<std::function<void()>>(
      [] { std::cout << "Zero " << std::endl; });

  auto error_observer =
      std::make_shared<std::function<void(const char*)>>([](const char* msg) {
        std::cout << "Error message: " << msg << std::endl;
      });

  Subject subject;
  subject.OnPositive::attach(positive_observer1);
  subject.OnPositive::attach(positive_observer2);
  subject.OnPositive::attach(throw_exception);
  subject.OnNegative::attach(negative_observer);
  subject.attach(zero_observer);
  subject.attach(error_observer);

  // any update on observable subject will notify its observers
  subject.Update(42);
  subject.Update(-1);
  subject.Update(0);
}
