// check if a string is a palindrome

#include <cassert>
#include <cctype>

#include <iostream>
#include <string>

auto next_alpha(const std::string& input, unsigned& index, unsigned limit) -> char {
    for (; index < limit; index++) {
        char c = input[index];
        if (std::isalpha(c)) {
            return tolower(c);
        }
    }
    throw std::exception{};
}

auto previous_alpha(const std::string& input, unsigned& index, unsigned limit) -> char {
    for (; index > limit; index--) {
        char c = input[index];
        if (std::isalpha(c)) {
            return tolower(c);
        }
    }
    throw std::exception{};
}

auto palindrome(const std::string& input) -> bool {
    unsigned i = 0;
    unsigned j = input.length() - 1;
    while (i < j) {
        try {
            auto c1 = next_alpha(input, i, j);
            auto c2 = previous_alpha(input, j, i);
            if (c1 != c2)
                return false;
        } catch (const std::exception&) {
            continue;
        }
        i++;
        j--;
    }
    return true;
}

int main() {
    assert(palindrome("aa"));
    assert(palindrome("a"));
    assert(palindrome("ana"));
    assert(palindrome("anna"));
    assert(palindrome("a na"));
    assert(palindrome("racecar"));
    assert(palindrome("Doc, note: I dissent. A fast never prevents a fatness. I diet on cod"));
    assert(!palindrome("banana"));
    assert(!palindrome("nana"));

    std::cout << "OK" << std::endl;
}
