#ifndef MODEL_DEPOSIT_H
#define MODEL_DEPOSIT_H

#include <qdatetime.h>

#include <QDialog>
#include <ctime>

namespace s21 {

struct ReplenishmentData {
  QVariant date;
  double amount;
};

struct DepositData {
  double deposit_sum;
  double months;
  double interest;
  double tax;
  int pay_freq_idx;
  int capitalization;
  double ac_interest;
  double sum_tax;
  double sum_total;
  QDate current_date;
  std::vector<ReplenishmentData> table;
};

class ModelDeposit {
 public:
  void setModel(DepositData data);
  void calculate();
  DepositData getResult();

 private:
  DepositData data_;
  void calculate_tax(double interest);
  QDate getReplenishmentDate(int row);
  double getReplenishmentAmount(int row);
};

}  // namespace s21

#endif  // MODEL_DEPOSIT_H
