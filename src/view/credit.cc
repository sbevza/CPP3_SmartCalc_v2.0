
#include "credit.h"
#include "ui_credit.h"

Credit::Credit(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Credit) {
    ui->setupUi(this);

    QLocale locale(QLocale::C);
    QDoubleValidator *creditSumValidator = new QDoubleValidator(0.0, 1000000000.0, 2, this);
    creditSumValidator->setLocale(locale);
    creditSumValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->ln_credit_sum->setValidator(creditSumValidator);

    QIntValidator *timeValidator = new QIntValidator(0, 100, this);
    ui->ln_time->setValidator(timeValidator);


    QDoubleValidator *interestValidator = new QDoubleValidator(0.0, 100.0, 2, this);
    interestValidator->setLocale(locale);
    ui->ln_interest->setValidator(interestValidator);

}

Credit::~Credit() {
    delete ui;
}

credit_model Credit::set_model() {
    credit_model model;
    model.credit_sum = ui->ln_credit_sum->text().toDouble();
    model.monthly_payment = 0;
    model.payment_from = 0;
    model.payment_to = 0;

    model.months = ui->ln_time->text().toDouble();
    if (ui->cmb_time->currentIndex() == 0) {
        model.months *= 12;
    }

    model.interest = ui->ln_interest->text().toDouble();

    model.type_idx = ui->cmb_type->currentIndex();
    return model;
}

void Credit::get_model(credit_model model) {
    if (model.type_idx) {
        ui->lb_monthly_payment_res->setText(
                QString::number(model.payment_from, 'f', 2) + " ... " + QString::number(model.payment_to, 'f', 2));
    } else {
        ui->lb_monthly_payment_res->setText(QString::number(model.monthly_payment, 'f', 2));
    }

    ui->lb_overpayment_res->setText(QString::number(model.overpay, 'f', 2));
    ui->lb_total_res->setText(QString::number(model.sum_total, 'f', 2));
}

void Credit::on_pushButton_clicked() {
    credit_model model = set_model();
    s21_credit(&model);
    get_model(model);
}


double Credit::calculate_annuity(double loan_amount, int months, double interest_rate) {
  double monthly_interest_rate = interest_rate / 1200.0;
  double annuity_factor =
      monthly_interest_rate / (1.0 - pow(1.0 + monthly_interest_rate, -months));
  return loan_amount * annuity_factor;
}

double Credit::calculate_differentiated(double loan_amount, int months,
                                double interest_rate, int month) {
  double monthly_interest_rate = interest_rate / 1200.0;
  double base = loan_amount / months;
  double interest = (loan_amount - base * (month - 1)) * monthly_interest_rate;
  return base + interest;
}

void Credit::s21_credit(credit_model *model) {
  if (!model->type_idx) {
    model->monthly_payment =
        calculate_annuity(model->credit_sum, model->months, model->interest);
    model->overpay = model->monthly_payment * model->months - model->credit_sum;
    model->sum_total = model->monthly_payment * model->months;
  } else {
    double payment = 0;
    double overpay = 0;
    for (int i = 1; i <= model->months; i++) {
      double monthly_payment = calculate_differentiated(
          model->credit_sum, model->months, model->interest, i);
      payment += monthly_payment;
      overpay += monthly_payment - model->credit_sum / model->months;
      if (i == 1) model->payment_from = monthly_payment;
      if (i == (model->months - 1)) model->payment_to = monthly_payment;
    }
    model->sum_total = payment;
    model->monthly_payment = model->sum_total / model->months;
    model->overpay = overpay;
  }
}




