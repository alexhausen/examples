#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

// classic fizzbuzz
auto fizzbuzz(int n) -> string {
  if (n % 15 == 0) {
    return "fizzbuzz";
  }
  if (n % 3 == 0) {
    return "fizz";
  }
  if (n % 5 == 0) {
    return "buzz";
  }
  stringstream ss;
  ss << n;
  return ss.str();
}

// fizzbuzz + bar(7) + bazz(13)
auto fizzbuzzbarbazz(int n) -> string {
  static const array<pair<int, string>, 5> a = {
      make_pair(15, "fizzbuzz"),  //
      make_pair(13, "bazz"),      //
      make_pair(7, "bar"),        //
      make_pair(5, "buzz"),       //
      make_pair(3, "fizz")        //
  };
  for (const auto& [k, v] : a) {
    if (n % k == 0) {
      return v;
    }
  }
  stringstream ss;
  ss << n;
  return ss.str();
}

auto main() -> int {
  for (int i = 1; i <= 100; ++i) {
    cout << fizzbuzzbarbazz(i) << endl;
  }
}
