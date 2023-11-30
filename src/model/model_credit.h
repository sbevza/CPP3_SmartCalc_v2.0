#ifndef MODEL_CREDIT_H
#define MODEL_CREDIT_H

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

class ModelCredit {
 public:
  void setModel(CreditData data);
  void calculate();
  CreditData getResult();

 private:
  CreditData data_;
  double calculate_annuity(double loan_amount, int months,
                           double interest_rate);
  double calculate_differentiated(double loan_amount, int months,
                                  double interest_rate, int month);
};

}  // namespace s21

#endif  // MODEL_CREDIT_H
