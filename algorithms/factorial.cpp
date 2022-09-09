// factorial(n!): recursive and iteractive

#include <cassert>

#include <iostream>

auto factorial_recursive(long n) -> long {
    if (n <= 1)
        return 1;
    return n * factorial_recursive(n - 1);
}

auto factorial_iteractive(long n) -> long {
    long r = 1;
    while (n > 1) {
        r *= n;
        n--;
    }
    return r;
}

int main() {
    assert(factorial_recursive(1) == 1);
    assert(factorial_recursive(2) == 2);
    assert(factorial_recursive(3) == 6);
    assert(factorial_recursive(7) == 7 * 6 * 5 * 4 * 3 * 2);

    assert(factorial_iteractive(1) == 1);
    assert(factorial_iteractive(2) == 2);
    assert(factorial_iteractive(3) == 6);
    assert(factorial_iteractive(7) == 7 * 6 * 5 * 4 * 3 * 2);

    std::cout << "OK" << std::endl;
}
