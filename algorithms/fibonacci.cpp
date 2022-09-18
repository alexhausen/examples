// fibonacci: iteractive and recursive + memoization

#include <cassert>

#include <array>
#include <iostream>
#include <optional>

auto fibonacci_recursive(long n) -> long {
    if (n < 2)
        return 1;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

auto fibonacci_iteractive(long n) -> long {
    if (n < 2)
        return 1;
    long r = 0;
    long acc1 = 1;
    long acc2 = 1;
    for (long i = 2; i <= n; i++) {
        r = acc1 + acc2;
        acc2 = acc1;
        acc1 = r;
    }
    return r;
}

// recursive implementation with memoization
template <std::integral T>
class memoization {
   public:
    memoization() { }

    auto put(const T& key, const T& value) -> void {
        if (0 <= key && key < max_entries)
            mem_[key] = std::optional{value};
    }

    auto get(const T& key) const noexcept -> std::optional<T> {
        if (0 <= key && key < max_entries)
            return mem_[key];
        return std::optional<T>{};
    }

   private:
    static constexpr T max_entries = 1000;

    std::array<std::optional<T>, max_entries> mem_;
};

auto fibonacci_memoization(long n) -> long {
    static memoization<decltype(n)> mem;
    if (n < 2)
        return 1;
    auto opt_value = mem.get(n);
    if (opt_value)
        return *opt_value;
    long value;
    value = fibonacci_memoization(n - 1) + fibonacci_memoization(n - 2);
    mem.put(n, value);
    return value;
}

int main() {
    assert(fibonacci_recursive(0) == 1);
    assert(fibonacci_recursive(1) == 1);
    assert(fibonacci_recursive(2) == 2);
    assert(fibonacci_recursive(3) == 3);
    assert(fibonacci_recursive(4) == 5);
    assert(fibonacci_recursive(5) == 8);
    assert(fibonacci_recursive(6) == 13);
    assert(fibonacci_recursive(7) == 21);

    assert(fibonacci_iteractive(0) == 1);
    assert(fibonacci_iteractive(1) == 1);
    assert(fibonacci_iteractive(2) == 2);
    assert(fibonacci_iteractive(3) == 3);
    assert(fibonacci_iteractive(4) == 5);
    assert(fibonacci_iteractive(5) == 8);
    assert(fibonacci_iteractive(6) == 13);
    assert(fibonacci_iteractive(7) == 21);

    assert(fibonacci_memoization(0) == 1);
    assert(fibonacci_memoization(1) == 1);
    assert(fibonacci_memoization(2) == 2);
    assert(fibonacci_memoization(3) == 3);
    assert(fibonacci_memoization(4) == 5);
    assert(fibonacci_memoization(5) == 8);
    assert(fibonacci_memoization(6) == 13);
    assert(fibonacci_memoization(7) == 21);

    std::cout << "OK" << std::endl;
}
