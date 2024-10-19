#include "s21_matrix_oop.h"

#include <cmath>
S21Matrix::S21Matrix() : S21Matrix(0, 0) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) throw std::invalid_argument("Incorrect input");
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  std::swap(other.matrix_, this->matrix_);
  other.RemoveMatrix();
}

S21Matrix::~S21Matrix() { RemoveMatrix(); }

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (matrix_ == nullptr && other.matrix_ == nullptr) return true;
  if (matrix_ == nullptr || other.matrix_ == nullptr) return false;
  bool res = (rows_ != other.rows_ || cols_ != other.cols_);
  for (int i = 0; i < rows_ && !res; ++i) {
    for (int j = 0; j < cols_ && !res; ++j) {
      res = (std::fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7);
    }
  }
  return !res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (matrix_ == nullptr || other.matrix_ == nullptr)
    throw std::invalid_argument("Impossible matrix");
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::runtime_error("Calculation error");
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (matrix_ == nullptr || other.matrix_ == nullptr)
    throw std::invalid_argument("Impossible matrix");
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::runtime_error("Calculation error");
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other(i, j);
    }
  }
}

void S21Matrix::MulNumber(double num) {
  if (matrix_ == nullptr) throw std::invalid_argument("Impossible matrix");
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (matrix_ == nullptr || other.matrix_ == nullptr)
    throw std::invalid_argument("Impossible matrix");
  if (cols_ != other.rows_) throw std::invalid_argument("Calculation error");
  S21Matrix tmp(rows_, other.cols_);
  for (int i = 0; i < tmp.rows_; ++i) {
    for (int j = 0; j < tmp.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        tmp(i, j) += matrix_[i][k] * other(k, j);
      }
    }
  }
  RemoveMatrix();
  *this = tmp;
}

S21Matrix S21Matrix::Transpose() const {
  if (matrix_ == nullptr) throw std::invalid_argument("Impossible matrix");
  S21Matrix tmp(cols_, rows_);
  for (int i = 0; i < cols_; ++i) {
    for (int j = 0; j < rows_; ++j) {
      tmp(i, j) = matrix_[j][i];
    }
  }
  return tmp;
}

double S21Matrix::Determinant() const {
  if (matrix_ == nullptr) throw std::invalid_argument("Impossible matrix");
  if (rows_ != cols_) throw std::invalid_argument("Calculation error");
  if (rows_ == 1) return matrix_[0][0];
  S21Matrix tmp(*this);
  double p = 1;
  if (tmp(0, 0) == 0) {
    for (int i = 1; i < rows_; ++i) {
      if (tmp(i, 0) != 0) {
        tmp.SwapRows(0, i);
        break;
      }
    }
  }
  for (int k = 0; k < rows_; ++k) {
    for (int i = k + 1; i < rows_; ++i) {
      for (int j = k + 1; j < cols_; ++j) {
        tmp(i, j) = (tmp(k, k) * tmp(i, j) - tmp(i, k) * tmp(k, j)) / p;
      }
    }

    p = tmp(k, k);
  }

  return tmp(rows_ - 1, rows_ - 1);
}

S21Matrix S21Matrix::CalcComplements() const {
  if (matrix_ == nullptr) throw std::invalid_argument("Impossible matrix");
  if (!Determinant()) throw std::invalid_argument("Calculation error");
  S21Matrix tmp(rows_, cols_);
  if (rows_ == 1) {
    tmp(0, 0) = matrix_[0][0];
    return tmp;
  }
  S21Matrix tmp_minor(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      FillMinor(i, j, tmp_minor);
      tmp(i, j) = pow(-1, i + j) * tmp_minor.Determinant();
    }
  }
  return tmp;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (matrix_ == nullptr) throw std::invalid_argument("Impossible matrix");
  if (!Determinant()) throw std::invalid_argument("Calculation error");
  if (rows_ == 1) {
    S21Matrix tmp(rows_, cols_);
    tmp(0, 0) = 1 / matrix_[0][0];
    return tmp;
  }
  return CalcComplements().Transpose() * (1 / Determinant());
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    CopyMatrix(other);
  }
  return *this;
}

double& S21Matrix::operator()(int row, int col) const {
  if (matrix_ == nullptr) {
    throw std::out_of_range("Matrix is not created");
  }
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row][col];
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix new_matrix(*this);
  new_matrix.SumMatrix(other);
  return new_matrix;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix new_matrix(*this);
  new_matrix.SubMatrix(other);
  return new_matrix;
}
S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix new_matrix(*this);
  new_matrix.MulNumber(num);
  return new_matrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix new_matrix(*this);
  new_matrix.MulMatrix(other);
  return new_matrix;
}

S21Matrix operator*(double num, const S21Matrix& other) {
  S21Matrix new_matrix(other);
  new_matrix.MulNumber(num);
  return new_matrix;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

void S21Matrix::CreateMatrix() {
  if (rows_ == 0 || cols_ == 0) {
    matrix_ = nullptr;
  } else {
    matrix_ = new double*[rows_]();

    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]();
    }
  }
}

void S21Matrix::RemoveMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::CopyMatrix(const S21Matrix& other) {
  CreateMatrix();
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      std::memcpy(matrix_[i], other.matrix_[i], other.cols_ * sizeof(double));
    }
  }
}

void S21Matrix::FillMinor(int r, int c, S21Matrix& tmp) const {
  for (int i = 0; i < tmp.rows_; i++) {
    for (int j = 0; j < tmp.cols_; j++) {
      tmp(i, j) = matrix_[(i >= r) ? i + 1 : i][(j >= c) ? j + 1 : j];
    }
  }
}

void S21Matrix::SwapRows(int r1, int r2) {
  S21Matrix tmp1(1, cols_);
  S21Matrix tmp2(1, cols_);
  for (int i = 0; i < cols_; i++) {
    tmp1(0, i) = matrix_[r1][i];
    tmp2(0, i) = matrix_[r2][i];
  }
  for (int i = 0; i < cols_; i++) {
    matrix_[r1][i] = tmp2(0, i);
    matrix_[r2][i] = (-1) * tmp1(0, i);
  }
}

void S21Matrix::set_rows(int rows) {
  S21Matrix new_martix(rows, cols_);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i < rows_) {
        new_martix(i, j) = matrix_[i][j];
      }
    }
  }
  RemoveMatrix();
  *this = new_martix;
}

void S21Matrix::set_cols(int cols) {
  S21Matrix new_martix(rows_, cols);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols; j++) {
      if (j < cols_) {
        new_martix(i, j) = matrix_[i][j];
      }
    }
  }
  RemoveMatrix();
  *this = new_martix;
}
