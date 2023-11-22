#ifndef C7_SMARTCALC_V1_0_0_S21_SMARTCALC_HPP
#define C7_SMARTCALC_V1_0_0_S21_SMARTCALC_HPP

#include <ctime>
#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <stdexcept>

namespace s21 {

struct CreditData {
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

struct DepositData {
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
  void s21_SmartCalc(const std::string &str_in, double x, double &res);
  void convert_to_poland();
  void setModel(const std::string &in, double x);
  int getErrorStatus();
  double getResult();

 private:
  static const int buffer_ = 255;
  std::string in_;
  std::string out_;
  std::string str_valid_;
  double x_;
  int error_;
  double result_;

  struct Stack {
    int top;
    char elements[Model::buffer_];
  };

  struct CalcStack {
    int top;
    double numbers[Model::buffer_];
  };


  void validate();
  int calculate();
  int execute(char c, std::vector<double> &st, int &pointer);
  int checkLength();
  int parse();
  int priorites(char c);
  Stack create_stack();
  int push(Stack &stack, char val);
  char peek(const Stack &stack);
  char pop(Stack &stack);
  int check_brackets();
  int check_dots(const std::string &str);
  int check_tigenometry();
  int check_pointer(char operation, int pointer);
};

} // namespace s21

#endif  // C7_SMARTCALC_V1_0_0_S21_SMARTCALC_HPP
