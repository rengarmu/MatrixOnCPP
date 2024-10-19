#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(constructor, square_mtx) {
  S21Matrix mtx(3, 3);
  EXPECT_EQ(mtx.cols(), 3);
  EXPECT_EQ(mtx.rows(), 3);
}

TEST(eq, test_1) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;
  m1(2, 0) = 7;
  m1(2, 1) = 8;
  m1(2, 2) = 9;
  S21Matrix m2 = m1;
  EXPECT_EQ(m1 == m2, true);
}

TEST(eq, test_2) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;
  m1(2, 0) = 7;
  m1(2, 1) = 8;
  m1(2, 2) = 9;
  S21Matrix m2 = m1;
  m2(1, 0) = 7;

  EXPECT_EQ(m1 == m2, false);
}

TEST(set_rows, test_1) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;
  m1(2, 0) = 7;
  m1(2, 1) = 8;
  m1(2, 2) = 9;
  m1.set_rows(4);
  EXPECT_EQ(m1(3, 0), 0);
}

TEST(set_rows, test_2) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;
  m1(2, 0) = 7;
  m1(2, 1) = 8;
  m1(2, 2) = 9;
  EXPECT_THROW(m1.set_rows(-4), std::invalid_argument);
}

TEST(set_cols, test_1) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;
  m1(2, 0) = 7;
  m1(2, 1) = 8;
  m1(2, 2) = 9;
  m1.set_cols(4);
  EXPECT_EQ(m1(0, 3), 0);
}

TEST(sum_matrix, test_1) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 1;
  m1(1, 1) = 2;
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 1;
  m2(1, 1) = 2;
  m1.SumMatrix(m2);
  EXPECT_EQ(m1(0, 0), 2);
  EXPECT_EQ(m1(0, 1), 4);
  EXPECT_EQ(m1(1, 0), 2);
  EXPECT_EQ(m1(1, 1), 4);
}

TEST(sum_matrix, test_2) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 1;
  m1(1, 1) = 2;
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 1;
  m2(1, 1) = 2;
  S21Matrix res = m1 + m2;
  EXPECT_EQ(res(0, 0), 2);
  EXPECT_EQ(res(0, 1), 4);
  EXPECT_EQ(res(1, 0), 2);
  EXPECT_EQ(res(1, 1), 4);
  EXPECT_EQ(m1(0, 0), 1);
  EXPECT_EQ(m1(0, 1), 2);
  EXPECT_EQ(m1(1, 0), 1);
  EXPECT_EQ(m1(1, 1), 2);
}

TEST(sum_matrix, test_3) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 1;
  m1(1, 1) = 2;
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 1;
  m2(1, 1) = 2;
  m1 += m1 + m2;
  EXPECT_EQ(m1(0, 0), 3);
  EXPECT_EQ(m1(0, 1), 6);
  EXPECT_EQ(m1(1, 0), 3);
  EXPECT_EQ(m1(1, 1), 6);
}

TEST(sub_matrix, test_1) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 3;
  m1(0, 1) = 6;
  m1(1, 0) = 3;
  m1(1, 1) = 6;
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 1;
  m2(1, 1) = 2;
  m1.SubMatrix(m2);
  EXPECT_EQ(m1(0, 0), 2);
  EXPECT_EQ(m1(0, 1), 4);
  EXPECT_EQ(m1(1, 0), 2);
  EXPECT_EQ(m1(1, 1), 4);
}

TEST(sub_matrix, test_2) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 6;
  m1(0, 1) = 6;
  m1(1, 0) = 6;
  m1(1, 1) = 6;
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 3;
  m2(1, 1) = 2;
  m1 -= m1 - m2;
  EXPECT_EQ(m1(0, 0), 1);
  EXPECT_EQ(m1(0, 1), 2);
  EXPECT_EQ(m1(1, 0), 3);
  EXPECT_EQ(m1(1, 1), 2);
}

TEST(sub_matrix, test_3) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 6;
  m1(0, 1) = 6;
  m1(1, 0) = 6;
  m1(1, 1) = 6;
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 3;
  m2(1, 1) = 4;
  S21Matrix res = m1 - m2;
  EXPECT_EQ(res(0, 0), 5);
  EXPECT_EQ(res(0, 1), 4);
  EXPECT_EQ(res(1, 0), 3);
  EXPECT_EQ(res(1, 1), 2);
}
TEST(mult_number, test_1) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  double num = 2;
  m1.MulNumber(num);
  EXPECT_EQ(m1(0, 0), 2);
  EXPECT_EQ(m1(0, 1), 4);
  EXPECT_EQ(m1(1, 0), 6);
  EXPECT_EQ(m1(1, 1), 8);
}

TEST(mult_number, test_2) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  S21Matrix res = m1 * 4;
  EXPECT_EQ(res(0, 0), 4);
  EXPECT_EQ(res(0, 1), 8);
  EXPECT_EQ(res(1, 0), 12);
  EXPECT_EQ(res(1, 1), 16);
}

TEST(mult_number, test_3) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  double num = 3;
  m1(0, 0) = 2;
  m1(0, 1) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1 *= num;
  EXPECT_EQ(m1(0, 0), 6);
  EXPECT_EQ(m1(0, 1), 9);
  EXPECT_EQ(m1(1, 0), 12);
  EXPECT_EQ(m1(1, 1), 15);
}

TEST(mult_number, test_4) {
  S21Matrix m1(3, 3);
  double num = 1.5;
  m1(0, 0) = 6;
  m1(0, 1) = 8;
  m1(0, 2) = 2;
  m1(1, 0) = 0;
  m1(1, 1) = 4;
  m1(1, 2) = 6;
  m1(2, 0) = 10;
  m1(2, 1) = 100;
  m1(2, 2) = 2;
  S21Matrix res = num * m1;
  EXPECT_EQ(res(0, 0), 9);
  EXPECT_EQ(res(0, 1), 12);
  EXPECT_EQ(res(0, 2), 3);
  EXPECT_EQ(res(1, 0), 0);
  EXPECT_EQ(res(1, 1), 6);
  EXPECT_EQ(res(1, 2), 9);
  EXPECT_EQ(res(2, 0), 15);
  EXPECT_EQ(res(2, 1), 150);
  EXPECT_EQ(res(2, 2), 3);
}

TEST(mul_matrix, test_1) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);
  m1(0, 0) = 2;
  m1(0, 1) = 4;
  m1(0, 2) = 6;
  m1(1, 0) = 3;
  m1(1, 1) = 5;
  m1(1, 2) = 4;
  m2(0, 0) = 5;
  m2(0, 1) = 2;
  m2(1, 0) = 4;
  m2(1, 1) = 3;
  m2(2, 0) = 7;
  m2(2, 1) = 9;
  m1.MulMatrix(m2);
  EXPECT_EQ(m1(0, 0), 68);
  EXPECT_EQ(m1(0, 1), 70);
  EXPECT_EQ(m1(1, 0), 63);
  EXPECT_EQ(m1(1, 1), 57);
}

TEST(mul_matrix, test_2) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);
  m1(0, 0) = 2;
  m1(0, 1) = 2;
  m1(0, 2) = 2;
  m1(1, 0) = 2;
  m1(1, 1) = 2;
  m1(1, 2) = 2;
  m2(0, 0) = 2;
  m2(0, 1) = 2;
  m2(1, 0) = 2;
  m2(1, 1) = 2;
  m2(2, 0) = 2;
  m2(2, 1) = 2;
  m1.MulMatrix(m2);
  EXPECT_EQ(m1(0, 0), 12);
  EXPECT_EQ(m1(0, 1), 12);
  EXPECT_EQ(m1(1, 0), 12);
  EXPECT_EQ(m1(1, 1), 12);
}

TEST(mul_matrix, test_3) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;
  m1(2, 0) = 7;
  m1(2, 1) = 8;
  m1(2, 2) = 9;
  S21Matrix res = m1 * m1;
  EXPECT_EQ(res(0, 0), 30);
  EXPECT_EQ(res(0, 1), 36);
  EXPECT_EQ(res(0, 2), 42);
  EXPECT_EQ(res(1, 0), 66);
  EXPECT_EQ(res(1, 1), 81);
  EXPECT_EQ(res(1, 2), 96);
  EXPECT_EQ(res(2, 0), 102);
  EXPECT_EQ(res(2, 1), 126);
  EXPECT_EQ(res(2, 2), 150);
}

TEST(mul_matrix, test_4) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 6;
  m1(0, 1) = 8;
  m1(0, 2) = 2;
  m1(1, 0) = 0;
  m1(1, 1) = 4;
  m1(1, 2) = 6;
  m1(2, 0) = 1;
  m1(2, 1) = 7;
  m1(2, 2) = 2;
  m1 *= m1;
  EXPECT_EQ(m1(0, 0), 38);
  EXPECT_EQ(m1(0, 1), 94);
  EXPECT_EQ(m1(0, 2), 64);
  EXPECT_EQ(m1(1, 0), 6);
  EXPECT_EQ(m1(1, 1), 58);
  EXPECT_EQ(m1(1, 2), 36);
  EXPECT_EQ(m1(2, 0), 8);
  EXPECT_EQ(m1(2, 1), 50);
  EXPECT_EQ(m1(2, 2), 48);
}

TEST(mul_matrix, test_5) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  S21Matrix m2(3, 3);
  m2(0, 0) = 4;
  EXPECT_THROW(S21Matrix res = m1 * m2, std::invalid_argument);
}

TEST(transpose, test_1) {
  S21Matrix m1(2, 4);
  m1(0, 0) = 2;
  m1(0, 1) = 5;
  m1(0, 2) = 1;
  m1(0, 3) = 7;
  m1(1, 0) = 0;
  m1(1, 1) = 3;
  m1(1, 2) = 9;
  m1(1, 3) = 5;
  S21Matrix res = m1.Transpose();
  EXPECT_EQ(res(0, 0), 2);
  EXPECT_EQ(res(1, 0), 5);
  EXPECT_EQ(res(2, 0), 1);
  EXPECT_EQ(res(3, 0), 7);
  EXPECT_EQ(res(0, 1), 0);
  EXPECT_EQ(res(1, 1), 3);
  EXPECT_EQ(res(2, 1), 9);
  EXPECT_EQ(res(3, 1), 5);
}

TEST(determinant, test_1) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 6;
  m1(0, 1) = 8;
  m1(0, 2) = 2;
  m1(1, 0) = 0;
  m1(1, 1) = 4;
  m1(1, 2) = 6;
  m1(2, 0) = 1;
  m1(2, 1) = 7;
  m1(2, 2) = 2;
  double det = m1.Determinant();
  EXPECT_EQ(det, -164);
}

TEST(determinant, test_2) {
  S21Matrix m1(4, 4);
  m1(0, 0) = 6;
  m1(0, 1) = 8;
  m1(0, 2) = 2;
  m1(0, 3) = 6;
  m1(1, 0) = 0;
  m1(1, 1) = 4;
  m1(1, 2) = 6;
  m1(1, 3) = 5;
  m1(2, 0) = 1;
  m1(2, 1) = 7;
  m1(2, 2) = 2;
  m1(2, 3) = 4;
  m1(3, 0) = 5;
  m1(3, 1) = 4;
  m1(3, 2) = 2;
  m1(3, 3) = 34;
  double det = m1.Determinant();
  EXPECT_EQ(det, -4878);
}

TEST(determinant, test_3) {
  S21Matrix mx1(4, 4);
  mx1(0, 0) = 60.42379715508781;
  mx1(0, 1) = 70.56372176004018;
  mx1(0, 2) = -96.62077687530758;
  mx1(0, 3) = 72.15586400416478;
  mx1(1, 0) = 49.342767499549325;
  mx1(1, 1) = -80.02157871207943;
  mx1(1, 2) = 48.18688616002598;
  mx1(1, 3) = 66.8214343688847;
  mx1(2, 0) = 33.981028157564396;
  mx1(2, 1) = 40.97011617957389;
  mx1(2, 2) = -72.30024032311428;
  mx1(2, 3) = 29.49265500451969;
  mx1(3, 0) = -69.40747037636834;
  mx1(3, 1) = 98.80610488251003;
  mx1(3, 2) = 90.82016910427797;
  mx1(3, 3) = 78.74262597081534;
  double res = mx1.Determinant();
  EXPECT_NEAR(res, 10626364.774005687, 1e-7);
}

TEST(determinant, test_4) {
  S21Matrix mx1(2, 3);
  double res;
  EXPECT_THROW(res = mx1.Determinant(), std::invalid_argument);
  res = 0;
  EXPECT_EQ(res, 0);
}

TEST(calc_complements, test_1) {
  S21Matrix m1(4, 4);
  m1(0, 0) = 6;
  m1(0, 1) = 8;
  m1(0, 2) = 2;
  m1(0, 3) = 6;
  m1(1, 0) = 0;
  m1(1, 1) = 4;
  m1(1, 2) = 6;
  m1(1, 3) = 5;
  m1(2, 0) = 1;
  m1(2, 1) = 7;
  m1(2, 2) = 2;
  m1(2, 3) = 4;
  m1(3, 0) = 5;
  m1(3, 1) = 4;
  m1(3, 2) = 2;
  m1(3, 3) = 34;
  S21Matrix res = m1.CalcComplements();
  EXPECT_EQ(res(0, 0), -1062);
  EXPECT_EQ(res(0, 1), 124);
  EXPECT_EQ(res(0, 2), -211);
  EXPECT_EQ(res(0, 3), 154);
  EXPECT_EQ(res(1, 0), -72);
  EXPECT_EQ(res(1, 1), 284);
  EXPECT_EQ(res(1, 2), -1034);
  EXPECT_EQ(res(1, 3), 38);
  EXPECT_EQ(res(2, 0), 1224);
  EXPECT_EQ(res(2, 1), -1034);
  EXPECT_EQ(res(2, 2), 776);
  EXPECT_EQ(res(2, 3), -104);
  EXPECT_EQ(res(3, 0), 54);
  EXPECT_EQ(res(3, 1), 58);
  EXPECT_EQ(res(3, 2), 98);
  EXPECT_EQ(res(3, 3), -164);
}

TEST(calc_complements, test_2) {
  S21Matrix mx1(1, 1);
  mx1(0, 0) = 1;
  S21Matrix res = mx1.CalcComplements();
  EXPECT_EQ(res(0, 0), 1);
}

TEST(calc_complements, test_3) {
  S21Matrix mx1(2, 1);

  EXPECT_THROW(S21Matrix res = mx1.CalcComplements(), std::invalid_argument);
}

TEST(inverse, test_1) {
  double EPS = 1e-7;
  S21Matrix mx1(4, 4);
  S21Matrix res(4, 4);

  mx1(0, 0) = 15.909057484071653;
  mx1(0, 1) = -97.55711673157266;
  mx1(0, 2) = 3.510808143068246;
  mx1(0, 3) = 31.82003717533891;
  mx1(1, 0) = -40.72276322817706;
  mx1(1, 1) = -27.516906010968953;
  mx1(1, 2) = 47.664409166309696;
  mx1(1, 3) = 93.99768459664065;
  mx1(2, 0) = 35.38138737283708;
  mx1(2, 1) = -52.840281425457945;
  mx1(2, 2) = 24.67340535157723;
  mx1(2, 3) = 92.58569538153117;
  mx1(3, 0) = 83.5211616438074;
  mx1(3, 1) = 79.9117414765368;
  mx1(3, 2) = 28.062407628803527;
  mx1(3, 3) = -98.3745054413039;

  res = mx1.InverseMatrix();
  EXPECT_NEAR(res(0, 0), -0.001694781385279976, EPS);
  EXPECT_NEAR(res(0, 1), -0.008065322643529842, EPS);
  EXPECT_NEAR(res(0, 2), 0.012176395508998402, EPS);
  EXPECT_NEAR(res(0, 3), 0.003205204268385977, EPS);
  EXPECT_NEAR(res(1, 0), -0.013275465958455489, EPS);
  EXPECT_NEAR(res(1, 1), -0.001549616327140123, EPS);
  EXPECT_NEAR(res(1, 2), 0.005530484276479666, EPS);
  EXPECT_NEAR(res(1, 3), -0.0005696845366228134, EPS);
  EXPECT_NEAR(res(2, 0), 0.009594778538722688, EPS);
  EXPECT_NEAR(res(2, 1), 0.018675172875359455, EPS);
  EXPECT_NEAR(res(2, 2), -0.01001619330342008, EPS);
  EXPECT_NEAR(res(2, 3), 0.011521003255465723, EPS);
  EXPECT_NEAR(res(3, 0), -0.00948582280577353, EPS);
  EXPECT_NEAR(res(3, 1), -0.0027790466701595293, EPS);
  EXPECT_NEAR(res(3, 2), 0.011973212191866065, EPS);
  EXPECT_NEAR(res(3, 3), -0.0046202520452419, EPS);
}

TEST(inverse, test_2) {
  S21Matrix mx1(1, 1);
  mx1(0, 0) = 1;
  S21Matrix res = mx1.InverseMatrix();
  EXPECT_EQ(res(0, 0), 1);
}

TEST(move, test_1) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2(std::move(m1));
  EXPECT_EQ(m2(0, 0), 1);
  EXPECT_EQ(m2.cols(), 2);
  EXPECT_EQ(m1.cols(), 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}