#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

template <typename T> class object;
template <typename T, typename... Args> object<T> make_object(Args&&...);
template <typename T> int count_object(const object<T>&);
template <typename T> T* get_object_ptr(const object<T>&);

template <typename T> class object {
private:
  explicit object(T* p) : px{ p } { assert(px != nullptr); }

public:
  object() = delete;
  ~object() noexcept = default;
  //destructor declaration automatically removes the implicity move constructor

  operator T&() const noexcept { return *px; }

  T& operator*() const noexcept { return *px; }

  T* operator->() const noexcept { return px.get(); }

  // not possible
  // T& operator.() const noexcept { return *px; }

private:
  shared_ptr<T> px;

  friend int count_object<T>(const object<T>&);
  friend T* get_object_ptr<T>(const object<T>&);
  template<typename T1, typename... A> friend object<T1> make_object(A&&...);
};

// auxiliary functions
template <typename T, typename... Args> object<T> make_object(Args&&... args) {
  return object<T>{ new T{ std::forward<Args>(args)... } };
}

template <typename T> int count_object(const object<T>& obj) {
  return obj.px.use_count();
}

template <typename T> T* get_object_ptr(const object<T>& obj) {
  return obj.px.get();
}

struct base {
  virtual void f() { cout << "base" << endl; }
};

struct extended : public base {
  virtual void f() override { cout << "extended" << endl; }
};

int main() {
  // runtime errors:
  // object<int> bang {nullptr};
  // object<int> bad;

  //object<int> o0{ new int{ 5 } };
  //cout << *o0 << endl;

  auto mo1 = make_object<int>(10);
  // will actually make a copy instead of 'move' (because a destructor was
  // declared)
  
  auto mo2 = std::move(mo1);
  cout << get_object_ptr(mo1) << ",count: " << count_object(mo1) << endl;
  cout << *mo1 << endl;

  auto o1 = object<string>{ make_object<string>("abc") };
  cout << *o1 << endl;

  vector<object<double> > v{ make_object<double>(1.0),
                             make_object<double>(2.0) };
  cout << "{ ";
  for (const auto& o : v) {
    cout << *o << " ";
  }
  cout << "}" << endl;

  extended ext;
  base& base_ref = ext;
  base_ref.f();

  auto o2 = make_object<extended>();
  o2->f();
  extended& ref2 = o2;
  ref2.f();
  (static_cast<extended&>(o2)).f();
  
  // operator. can not be overriden in c++ (and operator T&() won't do it)
  // o2.f();

  // why? how to do it?
  //  object<base> o3 = make_object<extended>();
  //  o3->f();
//  */
}

