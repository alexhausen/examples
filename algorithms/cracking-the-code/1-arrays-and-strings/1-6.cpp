/*
String Compression: Implement a method to perform basic string compression using the counts
of repeated characters. For example, the string aabcccccaaa would become a2b1c5a3. If the
"compressed" string would not become smaller than the original string, your method should return
the original string. You can assume the string has only uppercase and lowercase letters (a - z).
Hints:#92, #110
*/

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

std::string compress(const std::string& input) {
    if (input.size() <= 1)
        return input;
    std::stringstream ss;
    int count = 1;
    char last_char = input[0];
    for (unsigned i = 1; i < input.size(); i++) {
        char c = input[i];
        if (c == last_char) {
            count++;
        } else {
            ss << last_char;
            ss << count;
            count = 1;
            last_char = c;
        }
    }
    ss << last_char;
    ss << count;
    std::string result = ss.str();
    if (input.size() <= result.size()) {
        return input;
    }
    return result;
}

int main() {
    assert(compress("") == "");
    assert(compress("abc") == "abc");
    assert(compress("a") == "a");
    assert(compress("aa") == "aa");
    assert(compress("aaa") == "a3");
    assert(compress("aabcccccaaa") == "a2b1c5a3");
    std::cout << "OK" << std::endl;
}
