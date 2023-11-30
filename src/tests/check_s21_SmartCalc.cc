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
  EXPECT_EQ(m.getErrorStatus(), 2);
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
  EXPECT_EQ(result, 512);
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

TEST(Calc, test_calc_37) {
  double x = 0.0003;
  std::string input = "asin()";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_EQ(m.getErrorStatus(), 1);
}

TEST(Calc, test_calc_38) {
  double x = 0.0003;
  std::string input = "sqrt()";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_EQ(m.getErrorStatus(), 1);
}

TEST(Calc, test_calc_39) {
  double x = 0.0003;
  std::string input = "sqrt(\0)";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_EQ(m.getErrorStatus(), 1);
}

TEST(Calc, test_calc_40) {
  double x = 0.0003;
  std::string input = "log()";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_EQ(m.getErrorStatus(), 1);
}

TEST(Calc, test_calc_41) {
  double x = 0.0003;
  std::string input = std::string("(") + '\0' + ')';;
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_EQ(m.getErrorStatus(), 1);
}

TEST(Calc, test_calc_42) {
  double x = 0.0003;
  std::string input = "1234567890123456789012345678901234567890";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_43) {
  double x = 0.0003;
  std::string input = "1234567890123456789012345678901234567890^1234567890123456789012345678901234567890";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_44) {
  double x = 0.0003;
  std::string input = "acos(6)";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Calc, test_calc_45) {
  double x = 1.5;
  std::string input = "sin(x)+4/(2+x^2)-cos(2*x)";
  double result;
  s21::Model m;
  m.s21_SmartCalc(input, x, result);
  EXPECT_EQ(m.getErrorStatus(), 0);
}

TEST(Credit, test_calc_annuity) {
  s21::CreditData data = {1000000, 12, 15, 0, 0, 0, 0, 0, 0}; // Инициализация структуры
  s21::ModelCredit model;
  model.setModel(data);
  model.calculate();
  s21::CreditData result = model.getResult();

  EXPECT_NEAR(result.monthly_payment, 90258.31234515722, 1.0);
  EXPECT_NEAR(result.sum_total, 1083099.7481418867, 1.0);
  EXPECT_NEAR(result.overpay, 83099.74814188667, 1.0);
}

TEST(Credit, test_calc_differentiated) {
  s21::CreditData data = {1000000, 12, 15, 1, 0, 0, 0, 0, 0}; // Инициализация структуры
  s21::ModelCredit model;
  model.setModel(data);
  model.calculate();
  s21::CreditData result = model.getResult();

  EXPECT_NEAR(result.monthly_payment, 90104.16666666667, 1.0);
  EXPECT_NEAR(result.sum_total, 1081250, 1.0);
  EXPECT_NEAR(result.overpay, 81250, 1.0);
  EXPECT_NEAR(result.payment_from, 95833.33333333333, 1.0);
  EXPECT_NEAR(result.payment_to, 85416.66666666666, 1.0);
}

TEST(Deposit, TestCalculation) {
  s21::DepositData data = {1000000, 12, 10, 7.5, 0, 1, 0,
                           0, 0, QDate(2023, 1, 1), {
                               {QVariant(QDate(2023, 11, 30).toString("dd.MM.yyyy")), 10000.0},
                               {QVariant(QDate(2023, 12, 30).toString("dd.MM.yyyy")), -10000.0}
                           }};
  s21::ModelDeposit model;
  model.setModel(data);
  model.calculate();
  s21::DepositData result = model.getResult();

  EXPECT_NEAR(result.ac_interest, 105237.45, 1.0);
  EXPECT_NEAR(result.sum_total, 1105237.45, 1.0);
  EXPECT_NEAR(result.sum_tax, 3891.6228000000056, 1.0);
}

TEST(Deposit, TestCalculation2) {
  s21::DepositData data = {1000000, 12, 10, 7.5, 0, 0, 0,
                           0, 0, QDate(2023, 1, 1), {
                               {QVariant(QDate(2023, 11, 30).toString("dd.MM.yyyy")), 10000.0},
                               {QVariant(QDate(2023, 12, 30).toString("dd.MM.yyyy")), -10000.0}
                           }};
  s21::ModelDeposit model;
  model.setModel(data);
  model.calculate();
  s21::DepositData result = model.getResult();

  EXPECT_NEAR(result.ac_interest, 100080.5, 1.0);
  EXPECT_NEAR(result.sum_total, 1000000, 1.0);
  EXPECT_NEAR(result.sum_tax, 3224.9464000000626, 1.0);
}

TEST(Deposit, TestCalculation3) {
  s21::DepositData data = {1000000, 12, 10, 7.5, 2, 1, 0,
                           0, 0, QDate(2023, 1, 1), {
                               {QVariant(QDate(2023, 11, 30).toString("dd.MM.yyyy")), 10000.0},
                               {QVariant(QDate(2023, 12, 30).toString("dd.MM.yyyy")), -10000.0}
                           }};
  s21::ModelDeposit model;
  model.setModel(data);
  model.calculate();
  s21::DepositData result = model.getResult();

  EXPECT_NEAR(result.ac_interest, 103894.44, 1.0);
  EXPECT_NEAR(result.sum_total, 1103894.4399999999, 1.0);
  EXPECT_NEAR(result.sum_tax, 217.73569999999427, 1.0);
}

TEST(Deposit, TestCalculation4) {
  s21::DepositData data = {1000000, 12, 10, 7.5, 3, 1, 0,
                           0, 0, QDate(2023, 1, 1), {
                               {QVariant(QDate(2023, 11, 30).toString("dd.MM.yyyy")), 10000.0},
                               {QVariant(QDate(2023, 12, 30).toString("dd.MM.yyyy")), -10000.0}
                           }};
  s21::ModelDeposit model;
  model.setModel(data);
  model.calculate();
  s21::DepositData result = model.getResult();

  EXPECT_NEAR(result.ac_interest, 102581.02, 1.0);
  EXPECT_NEAR(result.sum_total, 1102581.02, 1.0);
  EXPECT_NEAR(result.sum_tax, 0, 1.0);
}

TEST(Deposit, TestCalculation5) {
  s21::DepositData data = {1000000, 12, 10, 7.5, 1, 1, 0,
                           0, 0, QDate(2023, 1, 1), {
                               {QVariant(QDate(2023, 11, 30).toString("dd.MM.yyyy")), 10000.0},
                               {QVariant(QDate(2023, 12, 30).toString("dd.MM.yyyy")), -10000.0}
                           }};
  s21::ModelDeposit model;
  model.setModel(data);
  model.calculate();
  s21::DepositData result = model.getResult();

  EXPECT_NEAR(result.ac_interest, 104879, 1.0);
  EXPECT_NEAR(result.sum_total, 1104879, 1.0);
  EXPECT_NEAR(result.sum_tax, 3953.5612999999994, 1.0);
}

TEST(Deposit, TestCalculation6) {
  s21::DepositData data = {10000000, 12, 10, 7.5, 4, 1, 0,
                           0, 0, QDate(2023, 1, 30), {}};
  s21::ModelDeposit model;
  model.setModel(data);
  model.calculate();
  s21::DepositData result = model.getResult();

  EXPECT_NEAR(result.ac_interest, 999776.75, 1.0);
  EXPECT_NEAR(result.sum_total, 10999776.75, 1.0);
  EXPECT_NEAR(result.sum_tax, 120220.97749999944, 1.0);
}

TEST(Deposit, TestCalculation7) {
  s21::DepositData data = {10000000, 12, 10, 7.5, 5, 1, 0,
                           0, 0, QDate(2023, 1, 30), {}};
  s21::ModelDeposit model;
  model.setModel(data);
  model.calculate();
  s21::DepositData result = model.getResult();

  EXPECT_NEAR(result.ac_interest, 999776.75, 1.0);
  EXPECT_NEAR(result.sum_total, 10999776.75, 1.0);
  EXPECT_NEAR(result.sum_tax, 120220.97749999944, 1.0);
}
