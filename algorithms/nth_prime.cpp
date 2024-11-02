#include <cassert>
#include <stdexcept>
#include <iostream>

bool is_prime(int n) {
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    int i = (n - 1) % 2 != 0 ? n - 1 : n - 2;
    for (; i > 2; i -= 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int next_prime(int p) {
    do {
        p++;
    } while (!is_prime(p));
    return p;
}

int nth_prime(int n) {
    if (n < 1) throw std::domain_error("error");
    int i = 1;
    int p = 2;
    while (i < n) {
        p = next_prime(p);
        i++;
    }
    return p;    
}

int main() {
  assert(2 == nth_prime(1));
  assert(3 == nth_prime(2));
  assert(13 == nth_prime(6));
  assert(104743 == nth_prime(10001));
  std::cout << "OK" << std::endl;
}
