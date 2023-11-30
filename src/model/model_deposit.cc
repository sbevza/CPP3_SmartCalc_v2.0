#include "model_deposit.h"
#include <qdatetime.h>
#include <math.h>
#include <QDialog>

namespace s21 {

void ModelDeposit::calculate() {
  data_.ac_interest = 0;
  data_.sum_tax = 0;
  data_.sum_total = data_.deposit_sum;

  double deposit_sum = data_.deposit_sum;
  double interest_rate = data_.interest;
  double remaining_balance = deposit_sum;
  double accrued_interest = 0;
  double prev_accrued_interest = 0;
  double period_interest = 0;
  int capitalization_freq = data_.pay_freq_idx;

  QDate current_date = data_.current_date;
  QDate begin_date = current_date;
  current_date = current_date.addDays(1);
  QDate end_date = current_date.addMonths(data_.months);
  unsigned long replenish_row = 0;
  int prev_year = current_date.year();
  while (current_date < end_date) {
    int days_in_year = QDate::isLeapYear(current_date.year()) ? 366 : 365;
    double daily_interest = remaining_balance * (interest_rate / days_in_year) / 100.0;
    period_interest += round(daily_interest * 100.0) / 100.0;

    if (current_date.year() != prev_year) {
        if  (capitalization_freq != 4)
          calculate_tax(accrued_interest - prev_accrued_interest);
      prev_year = current_date.year();
      prev_accrued_interest += accrued_interest;
    }

    if (capitalization_freq == 0) { // Каждый день
      if (data_.capitalization) remaining_balance += daily_interest;
      accrued_interest += period_interest;
      period_interest = 0;
    } else if (capitalization_freq == 1) { // Раз в месяц
      if (current_date.day() == begin_date.day()) {
        if (data_.capitalization) remaining_balance += period_interest;
        accrued_interest += period_interest;
        period_interest = 0;
      }
    } else if (capitalization_freq == 2) { // Раз в квартал
      if (current_date.day() == begin_date.day() &&
          (current_date.month() == begin_date.month() || current_date.month() == (begin_date.month() + 3) % 12 ||
              current_date.month() == (begin_date.month() + 6) % 12 ||
              current_date.month() == (begin_date.month() + 9) % 12)) {
        if (data_.capitalization) remaining_balance += period_interest;
        accrued_interest += period_interest;
        period_interest = 0;
      }
    } else if (capitalization_freq == 3) { // Раз в полгода
      if (current_date.day() == begin_date.day() &&
          (current_date.month() == begin_date.month() || current_date.month() == (begin_date.month() + 6) % 12)) {
        if (data_.capitalization) remaining_balance += period_interest;
        accrued_interest += period_interest;
        period_interest = 0;
      }
    } else if (capitalization_freq == 4) { // Раз в год
      if (current_date.day() == begin_date.day() &&
          current_date.month() == begin_date.month()) {
        if (data_.capitalization) remaining_balance += period_interest;
        accrued_interest += period_interest;
        period_interest = 0;
        calculate_tax(accrued_interest - prev_accrued_interest);
      }
    } else if (capitalization_freq == 5) {
      QDate tmp_date = end_date.addDays(-1);
      if (current_date == tmp_date) {
        if (data_.capitalization) remaining_balance += period_interest;
        accrued_interest += period_interest;
        calculate_tax(accrued_interest - prev_accrued_interest);
      }
    }

    if (replenish_row < data_.table.size()) {
      while ((replenish_row < data_.table.size()) &&
          (getReplenishmentDate(replenish_row) == current_date)) {
        double replenishment_amount = getReplenishmentAmount(replenish_row);
        remaining_balance += replenishment_amount;
        period_interest += replenishment_amount;
        data_.sum_total += replenishment_amount;
        replenish_row++;
      }
    }

    current_date = current_date.addDays(1);
  }

  data_.ac_interest = round(accrued_interest * 100) / 100;
  if (data_.capitalization) data_.sum_total += data_.ac_interest;
}

QDate ModelDeposit::getReplenishmentDate(int row) {
  QDate date;
  QVariant itemData = data_.table[row].date;
  QString dateString = itemData.toString();
  date = QDate::fromString(dateString, "dd.MM.yyyy");

  return date;
}

double ModelDeposit::getReplenishmentAmount(int row) {
  return data_.table[row].amount;
}

void ModelDeposit::calculate_tax(double interest) {
  double tax = data_.tax;
  double taxfree = 1000000.0 * (tax / 100.0);
  double sum_tax = (interest - taxfree) * (13.0 / 100.0);
  if (sum_tax > 0) data_.sum_tax += sum_tax;
}

void ModelDeposit::setModel(DepositData data) {
  data_ = data;
}

DepositData ModelDeposit::getResult() {
  return data_;
}
}
