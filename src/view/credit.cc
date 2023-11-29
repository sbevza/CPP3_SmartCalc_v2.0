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

void Credit::set_data() {
  s21::CreditData data;
  data.credit_sum = ui->ln_credit_sum->text().toDouble();
  data.monthly_payment = 0;
  data.payment_from = 0;
  data.payment_to = 0;
  data.overpay = 0;
  data.sum_total = 0;
  data.months = ui->ln_time->text().toDouble();
  if (ui->cmb_time->currentIndex() == 0) {
    data.months *= 12;
  }

  data.interest = ui->ln_interest->text().toDouble();

  data.type_idx = ui->cmb_type->currentIndex();

  controller->setCreditData(data);
}

void Credit::get_data() {
  s21::CreditData data = controller->getCreditData();
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
  set_data();
  controller->calculateCredit();
  get_data();
}

