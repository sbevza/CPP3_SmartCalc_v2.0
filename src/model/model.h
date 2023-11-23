#ifndef C7_SMARTCALC_V1_0_0_S21_SMARTCALC_HPP
#define C7_SMARTCALC_V1_0_0_S21_SMARTCALC_HPP

#include <ctime>
#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <stdexcept>

namespace s21 {

class Model {
 public:
  void s21_SmartCalc(const std::string &str_in, double x, double &res);
  void convert_to_poland();
  int calculate();
  void setModel(const std::string &in, double x);
  void reset();
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

  void validate();
  int execute(char c, std::vector<double> &st, int &pointer);
  int checkLength();
  int parse();
  int priorites(char c);
  int check_brackets();
  int check_dots(const std::string &str);
  int check_tigenometry();
  int check_pointer(char operation, int pointer);
};

} // namespace s21

#endif  // C7_SMARTCALC_V1_0_0_S21_SMARTCALC_HPP
