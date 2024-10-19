#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <iostream>

class S21Matrix {
 public:  // несколько способов инициализации объектов класса, по-другому
          // несколько конструкторов
  S21Matrix();  // конструктор по умолчанию (заранее заданные параметры)
  S21Matrix(int rows, int cols);          // parameterized constructor
  S21Matrix(const S21Matrix& other);      // copy cnstructor
  S21Matrix(S21Matrix&& other) noexcept;  // move cnstructor
  ~S21Matrix();                           // destructor

  inline int rows() const { return rows_; };
  inline int cols() const { return cols_; };
  void set_rows(int rows);
  void set_cols(int cols);

  // some operators overloads
  S21Matrix& operator=(const S21Matrix& other);  // assignment operator
  double& operator()(int row, int col) const;    // index operator
  bool operator==(const S21Matrix& other) const;

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(double num) const;
  S21Matrix operator*(const S21Matrix& other) const;
  friend S21Matrix operator*(double num, const S21Matrix& other);

  S21Matrix& operator*=(double num);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);

  // some public methods

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

 private:
  void CreateMatrix();
  void RemoveMatrix();
  void CopyMatrix(const S21Matrix& other);
  void FillMinor(int row, int col, S21Matrix& minor) const;
  void SwapRows(int row1, int row2);

  int rows_,
      cols_;  // rows and columns attributes
  double** matrix_ =
      nullptr;  // pointer to the memory where the matrix will be allocated
};

#endif
