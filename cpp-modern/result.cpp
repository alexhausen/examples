// Result class inpired by rust and std::expected

// g++ -std=c++20 -fno-exceptions -g3 -Wall -Wextra result.cpp

#include <cassert>
#include <iostream>
#include <string>
//#include <expected> // c++23 only

template <typename E>
struct Error final {
  constexpr explicit
  Error(E&& e) noexcept
  : error{std::forward<E>(e)} {}

  E error;
};

template <typename T, typename E>
class Result final {
public:
  template<typename U = T>
  constexpr explicit (!std::is_convertible_v<U, T>)
  Result(U&& u) noexcept
  : value_{std::forward<U>(u)}, has_value_{true} {}

  template<typename G = E>
  constexpr explicit (!std::is_convertible_v<G, E>)
  Result(Error<G>& u) noexcept
  : error_{u.error}, has_value_{false} { }

  template<typename G = E>
  constexpr explicit (!std::is_convertible_v<G, E>)
  Result(Error<G>&& u) noexcept
  : error_{std::move(u.error)}, has_value_{false} { }

  constexpr auto has_value() const noexcept -> bool {
    return has_value_;
  }

  constexpr operator bool () const noexcept {
    return has_value_;
  }

  constexpr auto has_error() const noexcept -> bool {
    return !has_value_;
  }

  constexpr auto value() const& noexcept -> const T& {
    return value_;
  }

  constexpr auto value() const&& noexcept -> T&& {
    return value_;
  }

  constexpr auto operator *() const& noexcept -> const T& {
    return value_;
  }

  constexpr auto operator *() const&& noexcept -> T&& {
    return value_;
  }

  constexpr auto error() const& noexcept -> const E& {
    return error_;
  }

  constexpr auto error() const&& noexcept -> E&& {
    return error_;
  }

  ~Result() noexcept {
    if (has_value_) {
      value_.~T();
    } else {
      error_.~E();
    }
  }

private:
  union {
    T value_;
    E error_;
  };
  bool has_value_;
};

enum class math_error {
  div_error
};

auto safe_int_div1(int a, int b) -> Result<int, math_error> {
  if (b == 0) {
    return Error(math_error::div_error);
  }
  return a / b;
}

auto safe_int_div2(int a, int b) -> Result<int, std::string> {
  if (b == 0) {
    return Error(std::string("division by zero"));
  }
  return a / b;
}

int main() {
  auto r1 = safe_int_div1(10, 2);
  assert(r1);
  assert(r1.has_value());
  assert(!r1.has_error());
  assert(*r1 == 5);
  assert(r1.value() == 5);

  auto r2 = safe_int_div2(10, 0);
  assert(!r2);
  assert(!r2.has_value());
  assert(r2.has_error());
  assert(r2.error() == "division by zero");

  std::cout << "OK" << std::endl;
}
