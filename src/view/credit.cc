#include "credit.h"
#include "ui_credit.h"

Credit::Credit(s21::Controller *controller, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Credit),
        controller(controller) {
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

s21::CreditData Credit::set_data() {
    s21::CreditData data;
    data.credit_sum = ui->ln_credit_sum->text().toDouble();
    data.monthly_payment = 0;
    data.payment_from = 0;
    data.payment_to = 0;

    data.months = ui->ln_time->text().toDouble();
    if (ui->cmb_time->currentIndex() == 0) {
        data.months *= 12;
    }

    data.interest = ui->ln_interest->text().toDouble();

    data.type_idx = ui->cmb_type->currentIndex();
    return data;
}

void Credit::get_data(s21::CreditData data) {
    if (data.type_idx) {
        ui->lb_monthly_payment_res->setText(
                QString::number(data.payment_from, 'f', 2) + " ... " + QString::number(data.payment_to, 'f', 2));
    } else {
        ui->lb_monthly_payment_res->setText(QString::number(data.monthly_payment, 'f', 2));
    }

    ui->lb_overpayment_res->setText(QString::number(data.overpay, 'f', 2));
    ui->lb_total_res->setText(QString::number(data.sum_total, 'f', 2));
}

void Credit::on_pushButton_clicked() {
    s21::CreditData data = set_data();
    s21_credit(&data);
    get_data(data);
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

void Credit::s21_credit(s21::CreditData *data) {
  if (!data->type_idx) {
    data->monthly_payment =
        calculate_annuity(data->credit_sum, data->months, data->interest);
    data->overpay = data->monthly_payment * data->months - data->credit_sum;
    data->sum_total = data->monthly_payment * data->months;
  } else {
    double payment = 0;
    double overpay = 0;
    for (int i = 1; i <= data->months; i++) {
      double monthly_payment = calculate_differentiated(
          data->credit_sum, data->months, data->interest, i);
      payment += monthly_payment;
      overpay += monthly_payment - data->credit_sum / data->months;
      if (i == 1) data->payment_from = monthly_payment;
      if (i == (data->months - 1)) data->payment_to = monthly_payment;
    }
    data->sum_total = payment;
    data->monthly_payment = data->sum_total / data->months;
    data->overpay = overpay;
  }
}




