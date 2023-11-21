#ifndef C7_SMARTCALC_V1_0_0_S21_SMARTCALC_HPP
#define C7_SMARTCALC_V1_0_0_S21_SMARTCALC_HPP

#include <ctime>
#include <string>
#include <vector>

namespace s21 {

struct CreditModel {
  double credit_sum;
  double months;
  double interest;
  int type_idx;
  double monthly_payment;
  double payment_from;
  double payment_to;
  double overpay;
  double sum_total;
};

struct DepositModel {
  double deposit_sum;
  double months;
  double days;
  std::tm begin_date;
  std::tm end_date;
  double interest;
  double tax;
  int pay_freq_idx;
  int capitalization;
  double ac_interest;
  double sum_tax;
  double sum_total;
};

class Model {
 public:
  int s21_SmartCalc(const std::string &str_in, double x, double &res);

 private:
  static const int buffer_ = 255;

  struct Stack {
    int top;
    char elements[Model::buffer_];
  };

  struct CalcStack {
    int top;
    double numbers[Model::buffer_];
  };

  static int validate(const std::string &in, std::string &out);
  static int convert_to_poland(const std::string &in, std::string &out);
  static int calculate(const std::string &in, double x, double &res);
  static int execute(char c, std::vector<double> &st, int &pointer);
  static int check_length(const std::string &str);
  static int parse(std::string &in, std::string &out);
  static int priorites(char c);
  static Stack create_stack();
  static int push(Stack &stack, char val);
  static char peek(const Stack &stack);
  static char pop(Stack &stack);
  static int check_brackets(const std::string &str);
  static int check_dots(const std::string &str);
};

} // namespace s21

#endif  // C7_SMARTCALC_V1_0_0_S21_SMARTCALC_HPP
