#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <math.h>
#include <QDialog>
#include "controller/controller.h"


namespace Ui {
class Deposit;
}

class Deposit : public QDialog {
  Q_OBJECT

 public:
  explicit Deposit(s21::Controller *controller, QWidget *parent = nullptr);
  ~Deposit();

 private slots:
  void on_pushButton_clicked();

  void on_bt_plus_clicked();

  void on_pushButton_Additions_minus_clicked();

 private:
  Ui::Deposit *ui;
  s21::Controller *controller;
  s21::DepositData setData();
  void get_model(s21::DepositData model);
  void s21_deposit(s21::DepositData *model);
  QDate getReplenishmentDate(int row);
  double getReplenishmentAmount(int row);
  void calculate_tax(s21::DepositData *model, double interest);
};

#endif  // DEPOSIT_H
