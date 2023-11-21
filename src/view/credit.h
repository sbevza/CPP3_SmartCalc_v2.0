#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>
#include <QIntValidator>
#include <math.h>

//extern "C" {
//#include "model/s21_SmartCalc.h"
//}

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::Credit *ui;
  credit_model set_model();
  void get_model(credit_model model);
  void s21_credit(credit_model *model);
  double calculate_differentiated(double loan_amount, int months,
                                  double interest_rate, int month);
  double calculate_annuity(double loan_amount, int months, double interest_rate);
};

#endif  // CREDIT_H
