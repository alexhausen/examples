/*
3.2
Stack Min: How would you design a stack which, in addition to push and pop, has a function min
which returns the minimum element? Push, pop and min should all operate in 0(1) time.
Hints: #27, #59, #78
*/

#include <cassert>
#include <iostream>
#include <vector>

struct node {
    node(int value, int min) : value{value}, min{min} {}

    int value;
    int min;
};

class stack_min {
   public:
    void push(int value) {  // O(1)
        int min_value = value;
        if (!st.empty()) {
            min_value = std::min(st.back().min, value);
        }
        st.push_back({value, min_value});
    }

    void pop() {
        if (st.empty())
            throw "stack is empty";
        st.pop_back();
    }  // O(1)

    int top() const { return st.back().value; }  // O(1)

    int min() const { return st.back().min; }  // O(1)

   private:
    std::vector<node> st;
};

int main() {
    stack_min st;
    st.push(42);
    assert(st.min() == 42);
    st.push(30);
    assert(st.min() == 30);
    st.push(33);
    assert(st.min() == 30);
    st.push(12);
    assert(st.min() == 12);

    st.pop();
    assert(st.min() == 30);
    st.pop();
    assert(st.min() == 30);
    st.pop();
    assert(st.min() == 42);

    std::cout << "OK" << std::endl;
}
