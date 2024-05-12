/*
8.12
Eight Queens: Write an algorithm to print all ways of arranging eight queens on
an 8x8 chess board so that none of them share the same row, column, or diagonal.
In this case, "diagonal" means all diagonals, not just the two that bisect the board.
Hints: #308, #350, #371
*/

#include <iostream>
#include <array>
#include <vector>

using namespace std;

// each row shall have a single queen,
// so we don't need to store the board 
// as a full 8x8 matrix
using queens_board_t = array<int, 8>;

bool valid_place(const queens_board_t& queens_board, int row, int col) {
  for (int r = 0; r < row; r++) {
    // don't need to check for the same row because our board representation
    // doesn't allow it

    int c = queens_board[r];
    if (col == c) {
      // the same column is already in use
      return false;
    }
  
    int col_distance = abs(col - c);
    int row_distance = row - r;
    if (row_distance == col_distance) {
      // when the row and column distances are the same,
      // then they are in the same diagonal
      return false;
    }
  }
  return true;
}

void place_queens(int row, queens_board_t& queens_board, vector<queens_board_t>& results) {
  if (row == 8) {
    results.push_back(queens_board);
    return;
  }
  for (int col = 0; col < 8; col++) {
    if (valid_place(queens_board, row, col)) {
      queens_board[row] = col; // place queen
      place_queens(row+1, queens_board, results);
    }
  }
}

vector<queens_board_t> place_all_queens() {
  queens_board_t columns;
  vector<queens_board_t> results;
  place_queens(0, columns, results);
  return results;
}

int main() {
  vector<queens_board_t> results = place_all_queens();
  for (const auto& board: results) {
    for (int r = 0; r < 8; ++r) {
      int c = board[r];
      cout << "(" << (r+1) << "," << (c+1) << ") ";
    }
    cout << std::endl;
  }
  cout << "OK" << endl;
}
