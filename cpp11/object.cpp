#include <cassert>
#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

template <typename T> class object {

public:
  object() = delete;

  object(T* p) : px{p} {
    assert(px != nullptr);
  }

  T& ref() noexcept {
    return *px;
  }

  T& ref() const noexcept {
    return *px;
  }

  T* get() noexcept {
    return px.get();
  }

  T* get() const noexcept {
    return px.get();
  }

private:
  shared_ptr<T> px;
};

int main() {

  //object<int> bang{ nullptr };

  object<int> o0{new int{5}};
  auto o1 = object<string>{new string{"abc"}};
  vector<object<double>> v { new double{ 0.1 }, new double { 0.2 } };

  cout << o0.ref() << endl;
  cout << o1.ref() << endl;
  for (const auto& o : v) {
    cout << o.ref() << " " << o.get() << endl;
  }

}
