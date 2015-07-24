#include <iostream>

template <int N>
int fat() {
  return N * fat<N-1>();
}

template <>
int fat<1>() {
  return 1;
}

int main() {
  const int fat5 = fat<5>();
  std::cout << fat5 << std::endl;
}
