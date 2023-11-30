#ifndef CREDIT_H
#define CREDIT_H

#include <math.h>

#include <QDialog>
#include <QIntValidator>

#include "controller/controller.h"

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(s21::Controller *controller, QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::Credit *ui;
  s21::Controller *controller;
  void set_data();
  void get_data();
  void s21_credit(s21::CreditData *data);
  double calculate_differentiated(double loan_amount, int months,
                                  double interest_rate, int month);
  double calculate_annuity(double loan_amount, int months,
                           double interest_rate);
};

#endif  // CREDIT_H
