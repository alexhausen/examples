/*
2.6
Palindrome: Implement a function to check if a linked list is a palindrome.
Hints: #5, #13, #29, #61, #101
*/

#include <cassert>
#include <forward_list>
#include <iostream>
#include <list>
#include <stack>

bool is_palindrome(const std::forward_list<char>& str) {
    std::stack<char> st;
    for (char c : str) {
        if (c != ' ')
            st.push(c);
    }
    for (char c1 : str) {
        if (c1 == ' ')
            continue;
        char c2 = st.top();
        if (c1 != c2)
            return false;
        st.pop();
    }
    return st.empty();
}

bool is_palindrome(const std::list<char>& str) {
    auto it = str.begin();
    auto rev = str.rbegin();
    while (it != str.end() && rev != str.rend()) {
        if (*it == ' ') {
            ++it;
            continue;
        }
        if (*rev == ' ') {
            ++rev;
            continue;
        }
        if (*it != *rev)
            return false;
        ++it;
        ++rev;
    }
    return true;
}

int main() {
    std::list<char> str0 = {};
    assert(is_palindrome(str0));
    std::list<char> str1 = {'a', 'b', 'c'};
    assert(!is_palindrome(str1));
    std::list<char> str2 = {'a', 'n', 'a'};
    assert(is_palindrome(str2));
    std::list<char> str3 = {'a', 'n', 'n', ' ', 'a'};
    assert(is_palindrome(str3));

    std::forward_list<char> fstr0 = {};
    assert(is_palindrome(fstr0));
    std::forward_list<char> fstr1 = {'a', 'b', 'c'};
    assert(!is_palindrome(fstr1));
    std::forward_list<char> fstr2 = {'a', 'n', 'a'};
    assert(is_palindrome(fstr2));
    std::forward_list<char> fstr3 = {'a', 'n', 'n', ' ', 'a'};
    assert(is_palindrome(fstr3));

    std::cout << "OK" << std::endl;
}
