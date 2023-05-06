/*
1.8
Zero Matrix: Write an algorithm such that if an element in an MxN matrix is 0, its entire row and
column are set to 0.
Hints:#17, #74, #102
*/

#include <cassert>
#include <iostream>
#include <vector>

using matrix = std::vector<std::vector<int32_t>>;

void zero_matrix(matrix& mat) {
    const unsigned m = mat.size();
    const unsigned n = mat[0].size();
    /*
    // TODO O(1) space
    for (unsigned i = 0; i < m; i++) {
        for (unsigned j = 0; j < n; j++) {
            if (mat[i][j] == 0) {
            }
        }
    }
    for (unsigned i = 0; i < m; i++) {
        for (unsigned j = 0; j < n; j++) {
            if ( ??? ) {
                mat[i][j] = 0;
            }
        }
    }
    */

    // O(n+m) space
    std::vector<bool> rows(m, false);
    std::vector<bool> columns(n, false);
    for (unsigned i = 0; i < m; i++) {
        for (unsigned j = 0; j < n; j++) {
            if (mat[i][j] == 0) {
                rows[i] = true;
                columns[j] = true;
            }
        }
    }
    for (unsigned i = 0; i < m; i++) {
        for (unsigned j = 0; j < n; j++) {
            if (rows[i] || columns[j]) {
                mat[i][j] = 0;
            }
        }
    }
}

int main() {
    matrix m1 = {
        {1, 0},
        {1, 1},
    };
    const matrix expected_m1 = {
        {0, 0},
        {1, 0},
    };
    zero_matrix(m1);
    assert(m1 == expected_m1);

    matrix m2 = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 8, 9},
    };
    const matrix expected_m2 = {
        {1, 0, 3},
        {0, 0, 0},
        {7, 0, 9},
    };
    zero_matrix(m2);
    assert(m2 == expected_m2);

    matrix m3 = {
        {1, 2},
        {3, 4},
        {5, 6},
    };
    const matrix expected_m3 = {
        {1, 2},
        {3, 4},
        {5, 6},
    };
    zero_matrix(m3);
    assert(m3 == expected_m3);

    std::cout << "OK" << std::endl;
}
