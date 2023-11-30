#include "model_credit.h"

#include <cmath>

namespace s21 {

void ModelCredit::calculate() {
  if (!data_.type_idx) {
    data_.monthly_payment =
        calculate_annuity(data_.credit_sum, data_.months, data_.interest);
    data_.overpay = data_.monthly_payment * data_.months - data_.credit_sum;
    data_.sum_total = data_.monthly_payment * data_.months;
  } else {
    double payment = 0;
    double overpay = 0;
    for (int i = 1; i <= data_.months; i++) {
      double monthly_payment = calculate_differentiated(
          data_.credit_sum, data_.months, data_.interest, i);
      payment += monthly_payment;
      overpay += monthly_payment - data_.credit_sum / data_.months;
      if (i == 1) data_.payment_from = monthly_payment;
      if (i == (data_.months - 1)) data_.payment_to = monthly_payment;
    }
    data_.sum_total = payment;
    data_.monthly_payment = data_.sum_total / data_.months;
    data_.overpay = overpay;
  }
}

double ModelCredit::calculate_annuity(double loan_amount, int months,
                                      double interest_rate) {
  double monthly_interest_rate = interest_rate / 1200.0;
  double annuity_factor =
      monthly_interest_rate / (1.0 - pow(1.0 + monthly_interest_rate, -months));
  return loan_amount * annuity_factor;
}

double ModelCredit::calculate_differentiated(double loan_amount, int months,
                                             double interest_rate, int month) {
  double monthly_interest_rate = interest_rate / 1200.0;
  double base = loan_amount / months;
  double interest = (loan_amount - base * (month - 1)) * monthly_interest_rate;
  return base + interest;
}

void ModelCredit::setModel(CreditData data) { data_ = data; }

CreditData ModelCredit::getResult() { return data_; }

}  // namespace s21
