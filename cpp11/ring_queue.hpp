// ring buffer queue
#include <iostream>

template <class T>
class ring_queue {
 public:
  ring_queue() : ring_queue{2} {}

  ring_queue(size_t capacity)
      : capacity{std::max(capacity, 2u)},
        size_{0},
        begin{0},
        end{0},
        buffer{new T[capacity]} {}
  ~ring_queue() { delete[] buffer; }

  bool empty() const noexcept { return size_ == 0; }

  size_t size() const noexcept { return size_; }

  void push(T&& item) {
    if (size() == capacity) {
      realloc_and_move();
    }
    if (end == capacity) end = 0;
    buffer[end] = std::move(item);
    ++end;
    ++size_;
  }

  void push(const T& item) {
    if (size() == capacity) {
      realloc_and_move();
    }
    if (end == capacity) end = 0;
    buffer[end] = item;
    ++end;
    ++size_;
  }

  T pop() {
    if (empty()) throw std::runtime_error{"error: buffer is empty"};
    size_t i = begin;
    begin = (begin + 1) % capacity;
    --size_;
    return std::move(buffer[i]);
  }

#ifndef NDEBUG
  void print() const {
    std::cout << "b: " << begin << ", e: " << end << ", s: " << size()
              << ", { ";
    const size_t sz = size();
    for (size_t i = 0; i < sz; ++i) {
      std::cout << buffer[(begin + i) % capacity] << " ";
    }
    std::cout << "} - [ ";
    for (size_t i = 0; i < capacity; ++i) {
      std::cout << buffer[i] << " ";
    }
    std::cout << "]" << std::endl;
  }
#endif

 private:
  void realloc_and_move() {
    //  reallocate twice the capacity and move elements
    size_t new_capacity = static_cast<float>(capacity) * 1.5f;
    T* new_buffer = new T[new_capacity];
    const size_t sz = size();
    size_t i = 0;
    for (; i < sz; ++i) {
      new_buffer[i] = std::move(buffer[(begin + i) % capacity]);
    }
    begin = 0;
    end = i;
    delete[] buffer;
    buffer = new_buffer;
    capacity = new_capacity;
  }

  size_t size_;
  size_t capacity;
  size_t begin;
  size_t end;
  T* buffer;
};
