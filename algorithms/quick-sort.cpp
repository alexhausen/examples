#include <cassert>

#include <algorithm>
#include <iostream>

// takes the last element as pivot;
// places the pivot element at its correct position in sorted array;
// places all smaller (smaller than pivot) to left of pivot
// and all greater elements to right of pivot.
template <typename T>
auto partition_c(T array[], int low, int high) -> int {
    auto pivot = array[high];
    // move smaller than the pivot to the <-
    for (auto i = low; i < high; i++) {
        if (array[i] < pivot) {
            std::swap(array[low], array[i]);
            low++;
        }
    }
    // move higher than the pivot to the ->
    std::swap(array[low], array[high]);
    // pivot index
    return low;
}

// quick sort C-array style
template <typename T>
auto quick_sort_c(T array[], int low, int high) -> void {
    if (low < high) {
        auto p = partition_c(array, low, high);
        quick_sort_c(array, low, p - 1);
        quick_sort_c(array, p + 1, high);
    }
}

template <typename Iter>
auto partition(Iter begin, Iter end) -> Iter {
    const auto pivot = *begin;
    auto low = begin;
    for (auto it = begin; it != end; ++it) {
        if (*it < pivot) {
            std::swap(*low, *it);
            ++low;
        }
    }
    std::swap(begin, low);
    return low;
}

// quick sort C++ STL style
template <typename Iter>
auto quick_sort(Iter lower, Iter upper) -> void {
    if (lower == upper)
        return;
    // points to an element in the middle of the sequence: lower+(upper-lower)/2
    const auto pivot_it = std::next(lower, std::distance(lower, upper) / 2);
    // partitions the sequence around the pivot: [< pivot] pivot [>= pivot]
    std::nth_element(lower, pivot_it, upper);
    quick_sort(lower, pivot_it);
    quick_sort(pivot_it + 1, upper);
}

template <typename Iter>
auto print(Iter begin, Iter end) -> void {
    std::cout << "[ ";
    for (auto it = begin; it != end; ++it)
        std::cout << *it << " ";
    std::cout << "] " << std::endl;
}

int main() {
    int array[] = {10, 0, 4, -1, 6, 7};
    print(std::begin(array), std::end(array));
    quick_sort_c<int>(array, 0, 5);
    print(std::begin(array), std::end(array));
    const int expected[] = {-1, 0, 4, 6, 7, 10};
    // assert(std::equal(array, array + 6, expected, expected + 6));
    assert(std::equal(std::begin(array), std::end(array),  //
                      std::begin(expected), std::end(expected)));

    std::vector<int> v = {10, 80, 30, 90, 40, 50, 70};
    print(v.begin(), v.end());
    quick_sort(v.begin(), v.end());
    print(v.begin(), v.end());
    const std::vector<int> expected_v = {10, 30, 40, 50, 70, 80, 90};
    assert(std::equal(v.begin(), v.end(), expected_v.begin(), expected_v.end()));
}
