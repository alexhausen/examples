// binary search tree

#include <cassert>

#include <concepts>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

template <class T>
struct TreeNode final {
    TreeNode(const T& value) noexcept : value_{value}, left_{nullptr}, right_{nullptr} {}

    auto leaf() const noexcept -> bool {  //
        return !left_ && !right_;
    }

    auto successor(TreeNode<T>* p) const -> TreeNode<T>* {
        if (p == nullptr)
            return nullptr;
        if (p->left_ == nullptr)
            return p;
        return successor(p->left_);
    }

    T value_;
    TreeNode<T>* left_;
    TreeNode<T>* right_;
};

template <class T>
class BinarySearchTree final {
   public:
    ~BinarySearchTree() noexcept {  //
        destroy_(root_);
    }

    auto empty() const noexcept -> bool {  //
        return root_ == nullptr;
    }

    // pre-order tree traversal
    auto pre_order(const std::function<void(const T&)>& fn) const noexcept -> void {  //
        pre_order_(this->root_, fn);
    }

    // in-order tree traversal
    auto in_order(const std::function<void(const T&)>& fn) const noexcept -> void {  //
        in_order_(this->root_, fn);
    }

    // post-order tree traversal
    auto post_order(const std::function<void(const T&)>& fn) const noexcept -> void {  //
        post_order_(this->root_, fn);
    }

    // deep-first search
    auto dfs(const T& value) const noexcept -> const TreeNode<T>* {
        TreeNode<T>* p = root_;
        while (p != nullptr) {
            if (value == p->value_)
                return p;
            p = value < p->value_ ? p->left_ : p->right_;
        }
        return nullptr;
    }

    // breath-first search
    auto bfs(const T& value) const noexcept -> const TreeNode<T>* {
        if (root_ == nullptr)
            return nullptr;
        std::queue<TreeNode<T>*> queue;
        queue.push(root_);
        while (!queue.empty()) {
            const auto* p = queue.front();
            queue.pop();
            if (value == p->value_)
                return p;
            if (p->left_ != nullptr)
                queue.push(p->left_);
            if (p->right_ != nullptr)
                queue.push(p->right_);
        }
        return nullptr;
    }

    auto depth() const noexcept -> unsigned {
        unsigned max = 0u;
        depth_(root_, 0u, max);
        return max;
    }

    auto smallest() const -> const T& {
        if (empty())
            throw std::exception();
        const TreeNode<T>* p = root_;
        while (p->left_ != nullptr) {
            p = p->left_;
        }
        return p->value_;
    }

    auto largest() const -> const T& {
        if (empty())
            throw std::exception();
        const TreeNode<T>* p = root_;
        while (p->right_ != nullptr) {
            p = p->right_;
        }
        return p->value_;
    }

    auto insert(const T& value) -> void {
        TreeNode<T>** pp = &root_;
        while (*pp != nullptr) {
            TreeNode<T>& r = **pp;
            if (value == r.value_)
                return;
            pp = value < r.value_ ? &r.left_ : &r.right_;
        }
        *pp = new TreeNode<T>(value);
    }

    auto remove(const T& value) noexcept -> void {  //
        root_ = remove_(root_, value);
    }

   private:
    static auto remove_(TreeNode<T>* p, const T& value) -> TreeNode<T>* {
        if (!p)
            return nullptr;
        if (value < p->value_) {
            p->left_ = remove_(p->left_, value);
        } else if (value > p->value_) {
            p->right_ = remove_(p->right_, value);
        } else {
            // 1) node to delete is leaf
            if (p->leaf()) {
                return nullptr;
            }
            // 2) node to delete has a single child
            if (p->left_ == nullptr) {
                auto* temp = p->right_;
                delete p;
                return temp;
            }
            if (p->right_ == nullptr) {
                auto* temp = p->left_;
                delete p;
                return temp;
            }
            // 3) node has 2 children
            auto* successor = p->successor(p->right_);
            p->value_ = successor->value_;
            p->right_ = remove_(p->right_, successor->value_);
        }
        return p;
    }

    static auto depth_(const TreeNode<T>* p, unsigned current, unsigned& max) noexcept -> void {
        if (p == nullptr)
            return;
        current++;
        if (current > max)
            max = current;
        depth_(p->left_, current, max);
        depth_(p->right_, current, max);
    }

    static auto pre_order_(const TreeNode<T>* p, const std::function<void(const T&)>& fn) noexcept
        -> void {
        if (p == nullptr)
            return;
        fn(p->value_);
        pre_order_(p->left_, fn);
        pre_order_(p->right_, fn);
    }

    static auto in_order_(const TreeNode<T>* p, const std::function<void(const T&)>& fn) noexcept
        -> void {
        if (p == nullptr)
            return;
        in_order_(p->left_, fn);
        fn(p->value_);
        in_order_(p->right_, fn);
    }

    static auto post_order_(TreeNode<T>* p, const std::function<void(const T&)>& fn) noexcept
        -> void {
        if (p == nullptr)
            return;
        post_order_(p->left_, fn);
        post_order_(p->right_, fn);
        fn(p->value_);
    }

    static auto destroy_(TreeNode<T>* p) noexcept {
        if (p == nullptr)
            return;
        destroy_(p->left_);
        destroy_(p->right_);
        delete p;
    }

    TreeNode<T>* root_ = nullptr;
};

static auto print_int(int value) noexcept -> void {
    std::cout << value << " ";
}

int main() {
    BinarySearchTree<int> t1;
    t1.insert(3);
    t1.insert(3);
    assert(t1.depth() == 1u);
    t1.insert(2);
    t1.insert(5);
    t1.insert(4);
    t1.insert(10);
    t1.insert(1);
    t1.insert(7);
    assert(t1.depth() == 4u);
    assert(t1.smallest() == 1);
    assert(t1.largest() == 10);

    BinarySearchTree<char> empty;
    assert(empty.empty());
    assert(empty.depth() == 0u);
    try {
        empty.smallest();
        assert(false);
    } catch (const std::exception&) {
    }
    try {
        empty.largest();
        assert(false);
    } catch (const std::exception&) {
    }

    // std::cout << "pre-order: ";
    // t1.pre_order(print_int);
    // std::cout << std::endl;
    std::vector<int> v1_pre;
    t1.pre_order([&](int value) noexcept { v1_pre.push_back(value); });
    std::vector<int> expected_v1_pre = {3, 2, 1, 5, 4, 10, 7};
    assert(v1_pre == expected_v1_pre);
    std::vector<int> empty_pre;
    empty.pre_order([&](char value) noexcept { empty_pre.push_back(value); });
    assert(empty_pre.empty());

    // std::cout << "in-order: ";
    // t1.in_order(print_int);
    // std::cout << std::endl;
    std::vector<int> v1_in;
    t1.in_order([&](int value) noexcept { v1_in.push_back(value); });
    std::vector<int> expected_v1_in = {1, 2, 3, 4, 5, 7, 10};
    assert(v1_in == expected_v1_in);
    std::vector<int> empty_in;
    empty.pre_order([&](char value) noexcept { empty_in.push_back(value); });
    assert(empty_in.empty());

    // std::cout << "post-order: ";
    // t1.post_order(print_int);
    // std::cout << std::endl;
    std::vector<int> v1_post;
    t1.post_order([&](int value) noexcept { v1_post.push_back(value); });
    std::vector<int> expected_v1_post = {1, 2, 4, 7, 10, 5, 3};
    assert(v1_post == expected_v1_post);
    std::vector<int> empty_post;
    empty.pre_order([&](char value) noexcept { empty_post.push_back(value); });
    assert(empty_post.empty());

    // deep-first search (dfs)
    assert(t1.dfs(7) != nullptr);
    assert(t1.dfs(3) != nullptr);
    assert(t1.dfs(10) != nullptr);
    assert(t1.dfs(1) != nullptr);
    assert(t1.dfs(42) == nullptr);
    assert(empty.dfs(1) == nullptr);

    // breath-first search (bfs)
    assert(t1.bfs(7) != nullptr);
    assert(t1.bfs(3) != nullptr);
    assert(t1.bfs(10) != nullptr);
    assert(t1.bfs(1) != nullptr);
    assert(t1.bfs(42) == nullptr);
    assert(empty.bfs(1) == nullptr);

    // remove
    empty.remove(1);
    assert(empty.empty());

    std::vector<int> v1;
    t1.remove(1);
    t1.pre_order([&](int value) noexcept { v1.push_back(value); });
    std::vector<int> expected_removed = {3, 2, 5, 4, 10, 7};
    assert(v1 == expected_removed);

    t1.remove(10);
    v1.clear();
    t1.pre_order([&](int value) noexcept { v1.push_back(value); });
    expected_removed = {3, 2, 5, 4, 7};
    assert(v1 == expected_removed);

    t1.remove(3);
    v1.clear();
    t1.pre_order([&](int value) noexcept { v1.push_back(value); });
    expected_removed = {4, 2, 5, 7};
    assert(v1 == expected_removed);

    t1.remove(3);
    t1.remove(2);
    v1.clear();
    t1.pre_order([&](int value) noexcept { v1.push_back(value); });
    expected_removed = {4, 5, 7};
    assert(v1 == expected_removed);
    t1.remove(4);
    t1.remove(5);
    t1.remove(7);
    assert(t1.empty());

    std::cout << "OK" << std::endl;
}
