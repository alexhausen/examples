#include <iostream>
#include <string>

template <class T>
class Enum {
public:
  Enum(T value):value_{value} { }
  virtual ~Enum() {}
  T get() const { return value_; }
  void set(T value) { value_ = value; }
  virtual void set(const std::string&) = 0;
  virtual std::string str() const = 0;

protected:
  T value_;
};

