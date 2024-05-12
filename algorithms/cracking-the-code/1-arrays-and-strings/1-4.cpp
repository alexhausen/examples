/*
1.4
Palindrome Permutation: Given a string, write a function to check if it is a permutation of a palin­
drome. A palindrome is a word or phrase that is the same forwards and backwards. A permutation
is a rearrangement of letters. The palindrome does not need to be limited to just dictionary words.
EXAMPLE
Input:Tact Coa
Output:True (permutations: "taco cat", "atco eta", etc.)
Hints: #106, #121, #134, #136
*/

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <array>

/*
bool is_palindrome(const std::string& input) {
    int j = input.size() - 1;
    const int n = input.size() / 2;
    for (int i = 0; i < n; i++, j--) {
        if (input[i] != input[j]) {
            return  false;
        }
    }
    return true;
}
*/

bool check_palindrome_of_permutation(const std::string& input) {
    /*
     too inefficient:
     for each permutation of input
       if (is_palindrome(permutation)) return true;
    */

    // using bit vector, reduce space, O(n) time
    std::array<bool, 26> odd_chars = {false};
    unsigned str_size = 0;
    for (char c1 : input) {
        char c = std::tolower(c1);
        if (std::isalpha(c)) {
            str_size++;
            odd_chars[c - 'a'] = !odd_chars[c - 'a'];
        }
    }
    unsigned odd_count = 0;
    for (unsigned i = 0; i < odd_chars.size(); i++) {
        odd_count += odd_chars[i]; // optimizion of: if (odd_chars[i]) odd_count++;
    }

    /*
    // using hash map
    std::unordered_map<char, int> mp;
    unsigned str_size = 0;
    for (char c : input) {
        if (isalpha(c)) { // remove non-alpha chars
            str_size++;
            mp[std::tolower(c)]++;
        }
    }
    unsigned odd_count = 0;
    for (const auto& [k, v] : mp) {
        if (v % 2 != 0) {
            odd_count++;
        }
    }
    */
    // if input size is odd there can be one char without a match
    // if input size is even every char must have a match
    return str_size % 2 == odd_count;
}

int main() {
    assert(check_palindrome_of_permutation("naA"));
    assert(check_palindrome_of_permutation("Tact Coa"));
    assert(check_palindrome_of_permutation(""));
    assert(!check_palindrome_of_permutation("nao"));
    std::cout << "OK" << std::endl;
}
