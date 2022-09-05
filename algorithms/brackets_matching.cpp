// check open-close parenthesis/squarre-bracket/curly-brackets balance

#include <cassert>

#include <iostream>
#include <stack>
#include <string>

auto is_open_bracket(char c) -> bool {
    return c == '(' || c == '[' || c == '{';
}

auto is_close_bracket(char c) -> bool {
    return c == ')' || c == ']' || c == '}';
}

auto brackets_macth(char open, char close) -> bool {
    return (open == '(' && close == ')') || (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

auto brackets_balance(const std::string& input) -> bool {
    std::stack<char> s;
    for (char c : input) {
        if (is_open_bracket(c)) {
            s.push(c);
        } else if (is_close_bracket(c)) {
            if (!s.empty() && brackets_macth(s.top(), c)) {
                s.pop();
            } else {
                return false;
            }
        }
    }
    return s.empty();
}

int main() {
    assert(brackets_balance(""));
    assert(brackets_balance("()"));
    assert(brackets_balance("[]"));
    assert(brackets_balance("{}"));
    assert(brackets_balance("([{}]{})()"));
    assert(brackets_balance("()()"));
    assert(brackets_balance("(()())"));
    assert(brackets_balance("(") == false);
    assert(brackets_balance(")") == false);
    assert(brackets_balance("[({") == false);
    assert(brackets_balance("({)}") == false);
    assert(brackets_balance("(()()") == false);
    assert(brackets_balance("()())") == false);

    std::cout << "OK" << std::endl;
}
