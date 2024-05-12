// TODO B-tree

#include <cassert>

#include <array>
#include <iostream>
#include <memory>
#include <vector>

template <typename T, unsigned N>
struct btree_node;

template <typename T, unsigned N>
using node_ptr = std::unique_ptr<btree_node<T, N>>;

template <typename T, unsigned N>
struct btree_node {
    std::vector<T> values_;
    std::array<node_ptr<T, N>, N + 1> nodes_;
};

template <typename T, unsigned N>
class btree {
   public:
    // insert

    // remove

    // search

    auto empty() const noexcept -> bool { return root_.get() == nullptr; }

   private:
    // join

    // split

    node_ptr<T, N> root_;
};

auto main() -> int {
    btree<int, 5> bt5;
    assert(bt5.empty());

    std::cout << "OK" << std::endl;
}