// max-heap (binary-tree array implementation)
// https://en.wikipedia.org/wiki/Heap_(data_structure)

#include <cassert>

#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T>
class max_heap final {
   public:
    max_heap() = default;

    max_heap(std::initializer_list<T> list) : heap_{list} { make_heap(); }

    // aka insert
    auto push(const T& value) -> void {
        heap_.push_back(value);
        sift_up();
    }

    // aka find_max, peek
    auto max() const -> const T& { return heap_.at(0); }

    // aka extract_max
    auto pop() -> T {
        auto value = heap_.at(0);
        sift_down();
        return value;
    }

    // aka pop & push (extract then insert)
    auto replace(const T& value) -> T {
        auto return_value = heap_.at(0);
        heap_[0] = value;
        heapfy(0);
        return return_value;
    }

    auto remove(const T& value) -> bool {
        int index = -1;
        for (unsigned i = 0; i < heap_.size(); i++) {
            if (heap_[i] == value) {
                index = static_cast<int>(i);
                break;
            }
        }
        if (index >= 0) {
            if (index != static_cast<int>(heap_.size()) - 1)
                heap_[index] = heap_.back();
            heap_.pop_back();
            heapfy(index);
        }
        return index != -1;
    }

    auto merge(const max_heap<T>& other) -> void {
        heap_.insert(heap_.end(), other.heap_.begin(), other.heap_.end());
        make_heap();
    }

    auto size() const noexcept -> unsigned { return heap_.size(); }

    auto empty() const noexcept -> bool { return size() == 0; }

    // move a node up in the tree, as long as needed
    // so the heap property is not violated
    auto sift_up() -> void {
        int child_index = heap_.size() - 1;
        while (child_index > 0) {
            int parent_idx = parent_index(child_index);
            auto& child = heap_[child_index];
            auto& parent = heap_[parent_idx];
            bool heap_property_violated = parent < child;
            if (!heap_property_violated)
                break;
            std::swap(parent, child);
            child_index = parent_idx;
        }
    }

    // move a node down in the tree, as long as needed
    // so the heap property is not violated
    auto sift_down() -> void {
        unsigned index = 0;
        if (heap_.size() > 1)
            heap_[index] = heap_.back();
        heap_.pop_back();
        heapfy(index);
    }

   private:
    std::vector<T> heap_;

    // aka bubble-down, percolate-down, sift-down, sink-down, trickle down,
    // heapify-down, cascade-down
    // this method assumes that the subtrees are already heapified
    auto heapfy(unsigned index) -> void {
        auto largest = index;
        while (has_child(index)) {
            auto left_index = left_child_index(index);
            if (left_index < heap_.size() && heap_[largest] < heap_[left_index])
                largest = left_index;
            auto right_index = right_child_index(index);
            if (right_index < heap_.size() && heap_[largest] < heap_[right_index])
                largest = right_index;
            bool heap_property_violated = largest != index;
            if (!heap_property_violated)
                break;
            std::swap(heap_[largest], heap_[index]);
            index = largest;
        }
    }

    auto has_child(unsigned index) const noexcept -> bool {
        return left_child_index(index) < heap_.size();
    }

    auto make_heap() -> void {
        int i = (static_cast<int>(heap_.size()) - 1) / 2;
        for (; i >= 0; i--) {
            heapfy(i);
        }
    }

    static auto parent_index(unsigned index) noexcept -> unsigned { return (index - 1) / 2; }

    static auto left_child_index(unsigned index) noexcept -> unsigned { return (index * 2) + 1; }

    static auto right_child_index(unsigned index) noexcept -> unsigned { return (index * 2) + 2; }
};

int main() {
    max_heap<int> h1;
    assert(h1.empty());
    assert(h1.size() == 0);

    h1.push(20);
    assert(h1.size() == 1);
    assert(h1.max() == 20);
    h1.push(34);
    h1.push(40);
    h1.push(10);
    h1.push(35);
    assert(h1.size() == 5);
    assert(h1.max() == 40);

    assert(h1.replace(25) == 40);
    assert(h1.size() == 5);

    h1.remove(35);

    assert(h1.pop() == 34);
    assert(h1.pop() == 25);
    assert(h1.pop() == 20);
    assert(h1.pop() == 10);
    assert(h1.empty());
    try {
        h1.pop();
        assert(false);
    } catch (const std::out_of_range&) {
    }

    max_heap<int> h2 = {20, 34, 40, 10, 35};
    assert(h2.size() == 5);
    assert(h2.pop() == 40);
    assert(h2.pop() == 35);
    assert(h2.pop() == 34);
    assert(h2.pop() == 20);
    assert(h2.pop() == 10);

    max_heap<int> h3 = {20, 34, 40, 10, 35};
    max_heap<int> h4 = {50, 12, 60, 44, 21, 20, 1};
    h3.merge(h4);
    assert(h3.size() == 12);
    assert(h3.pop() == 60);
    assert(h3.pop() == 50);
    assert(h3.pop() == 44);
    assert(h3.pop() == 40);
    assert(h3.pop() == 35);
    assert(h3.pop() == 34);
    assert(h3.pop() == 21);
    assert(h3.pop() == 20);
    assert(h3.pop() == 20);
    assert(h3.pop() == 12);
    assert(h3.pop() == 10);
    assert(h3.pop() == 1);

    std::cout << "OK" << std::endl;
}
