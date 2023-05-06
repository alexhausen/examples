// single and double linked lists

#include <cassert>

#include <iostream>
#include <stdexcept>

/*
class slist final {
};
*/

template <typename T>
class list final {
   public:
    list() : front_{nullptr} {}

    list(const std::initializer_list<T> input) : front_{nullptr} {
        for (const auto& value : input) {
            push_back(value);
        }
    }

    ~list() noexcept {
        node* current_node = front_;
        while (current_node) {
            node* temp = current_node;
            current_node = current_node->next_;
            delete temp;
        }
    }

    auto push_front(const T& value) -> void {
        node* old_node = front_;
        node* new_node = new node(value);
        new_node->next_ = old_node;
        if (old_node) {
            old_node->previous_ = new_node;
        }
        front_ = new_node;
    };

    auto pop_front() -> T {
        if (!front_)
            throw std::out_of_range{"pop empty list"};
        node* temp = front_;
        front_ = front_->next_;
        if (front_)
            front_->previous_ = nullptr;
        T value = temp->value_;
        delete temp;
        return value;
    }

    auto push_back(const T& value) -> void {
        // TODO
    }

    // auto pop_back() -> T {}

    // auto insert(i, const T&) -> void {}

    // auto remove(i) -> void {}

    auto at(size_t i) const -> T& {
        size_t count = 0;
        node* current_node = front_;
        while (current_node) {
            if (count == i)
                return current_node->value_;
            current_node = current_node->next_;
            count++;
        }
        throw std::out_of_range{"index out of range"};
    }

    auto empty() const noexcept -> bool { return front_ == nullptr; }

    auto size() const noexcept -> size_t {
        size_t size = 0;
        node* current_node = front_;
        while (current_node) {
            current_node = current_node->next_;
            size++;
        }
        return size;
    }

   private:
    struct node {
        node(const T& value) : value_{value}, previous_{nullptr}, next_{nullptr} {}
        T value_;
        node* previous_;
        node* next_;
    };

    struct iterator {
        // auto operator++() -> void {}
        // auto operator--() -> void {}
        // auto operator*() -> T& {}
       private:
        node* node_;
    };

    // reverse_iterator

    node* front_;
    // node* back_;

   public:
    // auto begin() -> iterator { return iterator{}; }

    // auto end() -> iterator {}

    // auto reverse_begin() -> reverse_iterator{}

    // auto reverse_end() -> reverse_iterator{}
};

auto main() -> int {
    list<int> l1;
    assert(l1.empty());
    assert(l1.size() == 0);
    l1.push_front(1);
    assert(!l1.empty());
    assert(l1.size() == 1);
    l1.push_front(2);
    assert(l1.size() == 2);
    assert(l1.at(0) == 2);
    assert(l1.at(1) == 1);
    try {
        l1.at(2);
        assert(false);
    } catch (const std::out_of_range& exception) {
        assert(std::string{exception.what()} == "index out of range");
    }
    assert(l1.pop_front() == 2);
    assert(l1.pop_front() == 1);
    assert(l1.empty());
    try {
        l1.pop_front();
        assert(false);
    } catch (const std::out_of_range& exception) {
        assert(std::string{exception.what()} == "pop empty list");
    }

    list<char> l2{'a', 'b', 'c'};
    assert(l2.size() == 3);
    assert(l2.at(0) == 'a');
    assert(l2.at(1) == 'b');
    assert(l2.at(2) == 'c');

    std::cout << "OK" << std::endl;
}
