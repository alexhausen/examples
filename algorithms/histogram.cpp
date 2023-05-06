//  A histogram shows the total number of occurrences for each number in a sequence.

#include <cassert>

#include <array>
#include <iostream>
#include <vector>

template <typename T, unsigned N>
auto make_histogram(const std::initializer_list<T> input, unsigned max_value) -> std::array<T, N> {
    std::array<T, N> histogram{0};
    unsigned bin_size = (max_value + 1) / N;
    for (auto& value : input) {
        // if value > max throw exception
        unsigned bucket = value / bin_size;
        histogram[bucket]++;
    }
    return histogram;
}

template <typename T, unsigned N>
auto print(const std::array<T, N>& h) {
    for (const auto& v : h) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

auto main() -> int {
    auto h0 = make_histogram<int, 1>({}, 1);
    std::array<int, 1> expected_h0 = {};
    assert(h0 == expected_h0);

    auto h1 = make_histogram<int, 2>({0, 1, 2}, 5);
    std::array<int, 2> expected_h1 = {3, 0};
    print<int, 2>(h1);
    assert(h1 == expected_h1);

    auto h2 = make_histogram<int, 3>({0, 1, 2, 3, 4}, 5);
    std::array<int, 3> expected_h2 = {2, 2, 1};
    print<int, 3>(h2);
    assert(h2 == expected_h2);

    std::cout << "OK" << std::endl;
}
