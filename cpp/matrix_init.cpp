#include <iostream>
#include <cstring>

class Matrix {
public:
  Matrix();
  void print();

private:
  int m_[2][4];
  static int s_[2][4];
};

Matrix::Matrix() {
  std::memcpy(m_, s_, 2 * 4 * sizeof(int));
}

int Matrix::s_[2][4] = {
  { 0, 1, 2, 3 },
  { 4, 5, 6, 7 } 
};

void Matrix::print() {
  for (unsigned int i = 0; i < 2; ++i) {
    for (unsigned int j = 0; j < 4; ++j) {
      std::cout << m_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  Matrix m1;
  m1.print();
}
