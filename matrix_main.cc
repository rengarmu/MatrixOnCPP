#include "s21_matrix_oop.h"

int main() {
  S21Matrix m1(3, 3);
  m1(0, 0) = 0;
  m1(0, 1) = 6;
  m1(0, 2) = 5;
  m1(1, 0) = 1;
  m1(1, 1) = 2;
  m1(1, 2) = 4;
  m1(2, 0) = 5;
  m1(2, 1) = 2;
  m1(2, 2) = 34;

  double res = m1.Determinant();
  std::cout << "res " << res << std::endl;
}