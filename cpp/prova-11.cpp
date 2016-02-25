#include <iostream>

template <int N>
long long fat() {
  return N * fat<N-1>();
}

template <>
long long fat<1>() {
  return 1;
}

int main() {
  const long long fat25 = fat<25>();
  std::cout << fat25 << std::endl;
}
