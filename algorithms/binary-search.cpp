// binary search

#include <cassert>

#include <algorithm>
#include <iostream>
#include <vector>

// traditional binary search implementation (recursive)
template <class T>
auto bin_search_recursive_impl(const T& value,
                               const std::vector<T>& vec,
                               unsigned lower,
                               unsigned upper) -> int {
    auto mid = lower + (upper - lower) / 2;
    if (vec[mid] == value) {
        return static_cast<int>(mid);
    }
    if (upper <= lower) {
        return -1;
    }
    if (value < vec[mid]) {
        upper = mid;
    } else {
        lower = mid + 1;
    }
    return bin_search_recursive_impl(value, vec, lower, upper);
}

template <class T>
auto binary_search_recursive(const T& value, const std::vector<T>& vec) -> int {
    return bin_search_recursive_impl(value, vec, 0, vec.size() - 1u);
}

// binary search implemantation using STL (iteractive)
template <class T, class Iter>
auto bin_search_stl(const T& value, Iter lower, Iter upper) -> Iter {
    auto end = upper;
    while (lower != upper) {
        // mid = lower + (upper - lower) / 2
        auto mid = std::next(lower, std::distance(lower, upper) / 2);
        if (value == *mid) {
            return mid;
        }
        if (value < *mid) {
            upper = mid;
        } else {
            lower = ++mid;
        }
    }
    return end;
}

template <class T>
auto binary_search_iteractive(const T& value, const std::vector<T>& vec) {
    return bin_search_stl(value, vec.cbegin(), vec.cend());
}

// binary search using std::lower_bound O(nlog(n))+O(1)
template <class T>
auto binary_search_iteractive2(const T& value, const std::vector<T>& vec) {
    return std::lower_bound(vec.cbegin(), vec.cend(), value);
}

int main() {
    std::vector<int> vec1{1, 2, 8, 11, 40, 99, 113, 200, 201, 230, 330};

    int index1 = binary_search_recursive(99, vec1);
    assert(5 == index1);
    int index2 = binary_search_recursive(100, vec1);
    assert(-1 == index2);
    int index3 = binary_search_recursive(1, vec1);
    assert(0 == index3);
    int index4 = binary_search_recursive(2, vec1);
    assert(1 == index4);
    int index5 = binary_search_recursive(330, vec1);
    assert(10 == index5);

    auto it1 = binary_search_iteractive(99, vec1);
    assert(it1 != vec1.cend());
    assert(99 == *it1);
    auto it2 = binary_search_iteractive(100, vec1);
    assert(it2 == vec1.cend());
    auto it3 = binary_search_iteractive(1, vec1);
    assert(it3 != vec1.cend());
    assert(1 == *it3);
    auto it4 = binary_search_iteractive(2, vec1);
    assert(it4 != vec1.cend());
    assert(2 == *it4);
    auto it5 = binary_search_iteractive(330, vec1);
    assert(it5 != vec1.cend());
    assert(330 == *it5);

    auto it6 = binary_search_iteractive2(230, vec1);
    assert(it6 != vec1.cend());
    assert(230 == *it6);
    auto it7 = binary_search_iteractive2(99, vec1);
    assert(it7 != vec1.cend());
    assert(99 == *it7);
    auto it8 = binary_search_iteractive(100, vec1);
    assert(it8 == vec1.cend());

    std::cout << "OK" << std::endl;
}
