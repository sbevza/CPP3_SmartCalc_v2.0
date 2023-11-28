#include "test_header.h"

TEST(Calc, test_calc_1) {
  std::string input = "5+7*2/(2-6)^3";
  double result = 0.0;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(result, 4.78125);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_2) {
  std::string input = "2+5+7+9*3*2^5";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(result, 878);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_3) {
  std::string input = "123.456+5*4^3";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(result, 443.456);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_4) {
  std::string input = "(8+2*5)/(1+3*2-4)";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(result, 6);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_5) {
  std::string input =
      "(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/2)))";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(result, 10);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_6) {
  std::string input = "cos(1*2)-1";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_NEAR(result, -1.41614683655, 1e-06);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_7) {
  std::string input =
      "cos(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
      "2)))-1";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_NEAR(result, -1.83907152908, 1e-06);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_8) {
  std::string input = "sin(cos(5))";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_NEAR(result, 0.27987335076, 1e-06);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_9) {
  std::string input = "2.33mod1";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_NEAR(result, 0.33, 1e-06);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_10) {
  double x = 10;
  std::string input = "3+4*2/1-5+2^2";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_NEAR(result, 10, 1e-06);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_11) {
  double x = 10;
  std::string input = "3+4*2/1-5+2^2";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_NEAR(result, 10, 1e-06);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_12) {
  double x = 0.0003;
  std::string input = "asin(2*x)";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_NEAR(result, 0.0006, 1e-06);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_13) {
  double x = 0.0019;
  std::string input = "acos(2*x)";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_NEAR(result, 1.567, 1e-03);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_14) {
  double x = 0.0019;
  std::string input = "atan(2*x)";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_NEAR(result, 0.00379998, 1e-06);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_15) {
  double x = 0.004;
  std::string input = "tan(2*x)";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_NEAR(result, 0.00800017, 1e-06);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_16) {
  double x = 25;
  std::string input = "sqrt(2*x)";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_NEAR(result, 7.07107, 1e-05);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_17) {
  double x = 2;
  std::string input = "ln(10*x)";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_NEAR(result, 2.99573, 1e-05);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_18) {
  double x = 2;
  std::string input = "log(10*x)";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_NEAR(result, 1.30103, 1e-05);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_19) {
  std::string input = "()";
  double result = 0;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_NEAR(result, 0, 1e-06);
  EXPECT_EQ(m.getErrorStatus(), 1);
}

TEST(Calc, test_calc_20) {
  std::string input = "3-(-3)";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_NEAR(result, 6, 1e-06);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_21) {
  std::string input = "-5-(-3)";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(result, -2);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_22) {
  std::string input = "-5(-3)";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(result, 15);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_23) {
  std::string input = "5/0";
  s21::Model m;
  double result;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(m.getErrorStatus(), 1);
}

TEST(Calc, test_calc_24) {
  std::string input = "mod5";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(m.getErrorStatus(), 1);
}

TEST(Calc, test_calc_25) {
  std::string input = "^2";
  s21::Model m;
  double result;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(m.getErrorStatus(), 1);
}

TEST(Calc, test_calc_26) {
  std::string input = "-3/(-3)";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(result, 1);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_27) {
  std::string input = "2^3^2";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(result, 64);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_28) {
  std::string input = "2^(3^2) ";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(result, 512);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_29) {
  std::string input = "((5-1)+2";
  double result = 0;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(m.getErrorStatus(), 1);
}

TEST(Calc, test_calc_30) {
  std::string input = "())(";
  double result = 0;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(m.getErrorStatus(), 1);
}

TEST(Calc, test_calc_31) {
  std::string input = "5.5.2+1";
  double result = 0;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(m.getErrorStatus(), 1);
}

TEST(Calc, test_calc_32) {
  std::string input = "z+1";
  double result = 0;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(m.getErrorStatus(), 1);
}

TEST(Calc, test_calc_33) {
  std::string input = "5+7^";
  double result = 0;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(m.getErrorStatus(), 1);
}

TEST(Calc, test_calc_34) {
  std::string input = "sin";
  double result = 0;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(m.getErrorStatus(), 1);
}

TEST(Calc, test_calc_35) {
  std::string input = "+1+2";
  double result = 0;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(m.getErrorStatus(), 0);
  EXPECT_EQ(result, 3);
}

TEST(Calc, test_calc_36) {
  std::string input = "sin5+1";
  double result = 0;
  s21::Model m;
  m.s21_SmartCalc(input, 0.0, result);
  EXPECT_EQ(m.getErrorStatus(), 1);
}

