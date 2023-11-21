#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <math.h>

#include <QDialog>

//extern "C" {
//#include "model/s21_SmartCalc.h"
//}

namespace Ui {
class Deposit;
}

class Deposit : public QDialog {
  Q_OBJECT

 public:
  explicit Deposit(QWidget *parent = nullptr);
  ~Deposit();

 private slots:
  void on_pushButton_clicked();

  void on_bt_plus_clicked();

  void on_pushButton_Additions_minus_clicked();

 private:
  Ui::Deposit *ui;
  deposit_model set_model();
  void get_model(deposit_model model);
  void s21_deposit(deposit_model *model);
  QDate getReplenishmentDate(int row);
  double getReplenishmentAmount(int row);
  void calculate_tax(deposit_model *model, double interest);
};

#endif  // DEPOSIT_H
