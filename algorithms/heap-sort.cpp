// heap sort

#include <cassert>

#include <iostream>

template <typename Iter>
auto print(Iter begin, Iter end) -> void {
    std::cout << "[ ";
    for (auto it = begin; it != end; ++it)
        std::cout << *it << " ";
    std::cout << "] " << std::endl;
}

// heap sort (STL style)
// see also: std::sort_heap
template <typename Iter, typename Cmp>
auto heap_sort(Iter begin, Iter end, const Cmp& cmp) -> void {
    std::make_heap(begin, end, cmp);
    while (std::distance(begin, end) > 1) {
        // remove top and place it at the back
        // heap property is kept in range [begin, end-1)
        std::pop_heap(begin, end, cmp);
        // print(begin, end);
        --end;
    }
}

template <typename Iter>
auto heap_sort(Iter begin, Iter end) -> void {
    // max heap (default)
    heap_sort(begin, end, std::less{});
}

int main() {
    int array[] = {9, 10, 0, 4, -1, 6, 7};
    int expected[] = {-1, 0, 4, 6, 7, 9, 10};
    heap_sort(std::begin(array), std::end(array));
    assert(std::equal(std::begin(array), std::end(array),  //
                      std::begin(expected), std::end(expected)));

    std::cout << "OK" << std::endl;
}
