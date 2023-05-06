/*
3.1
Three in One: Describe how you could use a single array to implement three stacks.
Hints: #2, #12, #38, #58
*/

#include <cassert>
#include <iostream>

class stack3 {
   public:
    stack3() {}

    void push(int stack_number, char value) {
        if (top3[stack_number] >= (stack_number + 1) * 10) {
            throw "stack full";
        }
        int pos = top3[stack_number];
        st3[pos] = value;
        top3[stack_number]++;
    }

    void pop(int stack_number) {
        if (top3[stack_number] <= (stack_number * 10)) {
            throw "stack empty";
        }
        top3[stack_number]--;
    }

    char top(int stack_number) const {
        int pos = top3[stack_number] - 1;
        return st3[pos];
    }

    bool empty(int stack_number) const { return top3[stack_number] == (stack_number * 10); }

   private:
    int top3[3] = {0, 10, 20};
    char* st3 = new char[30];
};

int main() {
    stack3 st3;

    assert(st3.empty(0));
    assert(st3.empty(1));
    assert(st3.empty(2));

    st3.push(0, 'a');
    st3.push(0, 'b');
    st3.push(0, 'c');

    st3.push(1, 'd');
    st3.push(1, 'e');
    st3.push(1, 'f');

    st3.push(2, 'g');
    st3.push(2, 'h');
    st3.push(2, 'i');

    assert(!st3.empty(0));
    assert(!st3.empty(1));
    assert(!st3.empty(2));

    assert(st3.top(0) == 'c');
    assert(st3.top(1) == 'f');
    assert(st3.top(2) == 'i');

    st3.pop(0);
    st3.pop(1);
    st3.pop(2);

    assert(st3.top(0) == 'b');
    assert(st3.top(1) == 'e');
    assert(st3.top(2) == 'h');

    st3.pop(0);
    st3.pop(1);
    st3.pop(2);

    assert(st3.top(0) == 'a');
    assert(st3.top(1) == 'd');
    assert(st3.top(2) == 'g');

    st3.pop(0);
    st3.pop(1);
    st3.pop(2);

    assert(st3.empty(0));
    assert(st3.empty(1));
    assert(st3.empty(2));

    std::cout << "OK" << std::endl;
}
