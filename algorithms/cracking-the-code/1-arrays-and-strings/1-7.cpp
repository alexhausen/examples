/*
1.7
Rotate Matrix: Given an image represented by an NxN matrix, where each pixel in the image is 4
bytes, write a method to rotate the image by 90 degrees. Can you do this in place?
Hints:#51, #100
*/

#include <cassert>
#include <iostream>
#include <vector>

using matrix = std::vector<std::vector<int32_t>>;

void rotate90inplace(matrix& m) {
    // TODO
}

matrix rotate90(const matrix& m) {
    matrix m2;
    const unsigned n = m.size();
    m2.resize(n);
    for (unsigned i = 0; i < n; i++) {
        m2[i].resize(n);
    }
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            m2[j][n - i - 1] = m[i][j];
        }
    }
    return m2;
}

void print(const matrix& m) {
    for (unsigned i = 0; i < m.size(); i++) {
        std::cout << "|";
        for (unsigned j = 0; j < m[i].size(); j++) {
            std::cout << " " << m[i][j];
        }
        std::cout << " |" << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    matrix m1 = {
        {1, 2},
        {3, 4},
    };
    const matrix expected_m1_90 = {
        {3, 1},
        {4, 2},
    };

    assert(rotate90(m1) == expected_m1_90);

    rotate90inplace(m1);
    assert(m1 == expected_m1_90);

    matrix m2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };
    const matrix expected_m2_90 = {
        {7, 4, 1},
        {8, 5, 2},
        {9, 6, 3},
    };

    assert(rotate90(m2) == expected_m2_90);

    rotate90inplace(m2);
    assert(m2 == expected_m2_90);

    std::cout << "OK" << std::endl;
}
