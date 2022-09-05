// binary search

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

// traditional binary search implementation (recursive)
template <class T>
int bin_search_impl(const T& value, const std::vector<T>& vec, unsigned lower, unsigned upper) {
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
    return bin_search_impl(value, vec, lower, upper);
}

template <class T>
int bin_search1(const T& value, const std::vector<T>& vec) {
    return bin_search_impl(value, vec, 0, vec.size() - 1u);
}

// binary search implemantation using STL (non-recursive)
template <class Iter, class T>
Iter bin_search_stl(const T& value, Iter lower, Iter upper) {
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
auto bin_search2(const T& value, const std::vector<T>& vec) {
    return bin_search_stl(value, vec.cbegin(), vec.cend());
}

int main() {
    std::vector<int> vec1{1, 2, 8, 11, 40, 99, 113, 200, 201, 230, 330};

    int index1 = bin_search1(99, vec1);
    assert(5 == index1);
    int index2 = bin_search1(100, vec1);
    assert(-1 == index2);
    int index3 = bin_search1(1, vec1);
    assert(0 == index3);
    int index4 = bin_search1(2, vec1);
    assert(1 == index4);
    int index5 = bin_search1(330, vec1);
    assert(10 == index5);

    auto it1 = bin_search2(99, vec1);
    assert(it1 != vec1.cend());
    assert(99 == *it1);
    auto it2 = bin_search2(100, vec1);
    assert(it2 == vec1.cend());
    auto it3 = bin_search2(1, vec1);
    assert(it3 != vec1.cend());
    assert(1 == *it3);
    auto it4 = bin_search2(2, vec1);
    assert(it4 != vec1.cend());
    assert(2 == *it4);
    auto it5 = bin_search2(330, vec1);
    assert(it5 != vec1.cend());
    assert(330 == *it5);

    std::cout << "OK" << std::endl;
}
