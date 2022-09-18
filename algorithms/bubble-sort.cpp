// bubble sort

#include <cassert>

#include <algorithm>
#include <iostream>
#include <vector>

// bubble sort C-array style
template <typename T>
auto bubble_sort_c(T array[], unsigned n) -> void {
    for (unsigned i = 0; i < n; i++)
        for (unsigned j = i + 1; j < n; j++)
            if (array[i] > array[j])
                std::swap(array[i], array[j]);
}

// bubble sort C++ STL style
template <class Iter>
auto bubble_sort(Iter begin, Iter end) -> void {
    for (auto it1 = begin; it1 != end; ++it1)
        for (auto it2 = it1 + 1; it2 != end; ++it2)
            if (*it1 > *it2)
                std::swap(*it1, *it2);
}

int main() {
    int array[] = {10, 0, 4, -1, 6, 7};
    bubble_sort_c<int>(array, 6);
    int expected[] = {-1, 0, 4, 6, 7, 10};
    //assert(std::equal(array, array + 6, expected, expected + 6));
    assert(std::equal(std::begin(array), std::end(array),  //
                      std::begin(expected), std::end(expected)));

    std::vector<int> vec = {10, 0, 4, -1, 6, 7};
    bubble_sort(vec.begin(), vec.end());
    assert(std::equal(std::begin(vec), std::end(vec),  //
                      std::begin(expected), std::end(expected)));

    std::cout << "OK" << std::endl;
}
