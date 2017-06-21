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
    if (size_ == capacity) {
      realloc_and_move();
    }
    if (end == capacity) end = 0;
    buffer[end] = std::move(item);
    ++end;
    ++size_;
  }

  void push(const T& item) {
    if (size_ == capacity) {
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
    std::cout << "b: " << begin << ", e: " << end << ", s: " << size_ << ", { ";
    if (begin < end) {
      for (size_t i = begin; i < end; ++i) {
        std::cout << buffer[i] << " ";
      }
    } else if (end > 0) {
      for (size_t i = begin; i < capacity; ++i) {
        std::cout << buffer[i] << " ";
      }
      for (size_t i = end - 1; i < begin; ++i) {
        std::cout << buffer[i] << " ";
      }
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
    size_t j = 0;
    if (begin < end) {
      for (size_t i = begin; i < end; ++i, ++j) {
        new_buffer[j] = std::move(buffer[i]);
      }
    } else if (end > 0) {
      for (size_t i = begin; i < capacity; ++i, ++j) {
        new_buffer[j] = std::move(buffer[i]);
      }
      for (size_t i = end - 1; i < begin; ++i, ++j) {
        new_buffer[j] = std::move(buffer[i]);
      }
    }
    begin = 0;
    end = j;
    delete[] buffer;
    buffer = new_buffer;
    capacity = new_capacity;
  }

  size_t capacity;
  size_t size_;
  size_t begin;
  size_t end;
  T* buffer;
};
