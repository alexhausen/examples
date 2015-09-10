#include <cassert>


template <typename T>
class stack {

 private:
  struct node {
    T value;
    node* next;
  };

  int count_;
  node* top_;

 public:
  stack() : count_(0), top_(nullptr) {
  }

  ~stack() {
    while (top_) {
      node* n = top_;
      top_ = top_->next;
      delete n;
      count_--;
    }
  }

  void push(T c) {
    node* n = new node();
    n->value = c;
    n->next = top_;
    top_ = n;
    count_++;
  }

  bool pop() {
    if (count_ > 0) {
      node* n = top_;
      top_ = top_->next;
      delete n;
      count_--;
      return true;
    }
    return false;
  }

  T top() const {
    //if !top_ throw "invalid top exception"
    return top_->value;
  }

  unsigned int size() const {
    return count_;
  }
};


int main() {

  stack<char> s;
  s.push('s');
  s.push('t');
  s.push('a');
  s.push('c');
  s.push('k');

  assert(s.size() == 5);
  assert(s.top() == 'k');
  assert(s.pop());
  assert(s.size() == 4);
  assert(s.top() == 'c');

  assert(s.pop());
  assert(s.pop());
  assert(s.pop());
  assert(s.pop());
  assert(s.pop() == false);
  assert(s.size() == 0);

}
