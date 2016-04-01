#include <iostream>
#include <string>

template <class T>
void print(const T* data, int size) {
  for (int i = 0; i < size; ++i) {
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}


int main() {
  int a[] = { 1, 2, 3, 4 };
  double b[] = { 1.0, 2.0, 3.0 };
  std::string c[] = { "abc", "xyz" };
  print(a, 4);
  print(b, 3);
  print(c, 2);
}