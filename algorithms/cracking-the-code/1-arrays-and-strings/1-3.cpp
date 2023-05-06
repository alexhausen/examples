/*
1.3
URLify: Write a method to replace all spaces in a string with '%20'. You may assume that the string
has sufficient space at the end to hold the additional characters, and that you are given the "true"
length of the string. (Note: If implementing in Java, please use a character array so that you can
perform this operation in place.)
EXAMPLE
Input:"Mr John Smith", 13
Output:"Mr%20John%20Smith"
Hints: #53, #118
*/

#include <cassert>
#include <string>
#include <iostream>

void urlfy(std::string& str, int size) {

    int j = str.size() - 1;
    for (int i = size - 1; i >= 0; i--) {
        if (str[i] != ' ') {
            str[j--] = str[i];
        } else {
            str[j--] = '0';
            str[j--] = '2';
            str[j--] = '%';
        }
    }
}

int main() {
    std::string str("Mr John Smith    ");
    urlfy(str, 13);
    std::cout << str << std::endl;
    assert(str == std::string("Mr%20John%20Smith"));
    std::cout << "OK" << std::endl;
}
