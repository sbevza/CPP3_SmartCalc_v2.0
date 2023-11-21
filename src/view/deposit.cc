#include "deposit.h"
#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Deposit) {
    ui->setupUi(this);
    ui->de_begin_date->setDate(QDate::currentDate());

    QLocale locale(QLocale::C);
    QDoubleValidator *depositSumValidator = new QDoubleValidator(0.0, 1000000000.0, 2, this);
    depositSumValidator->setLocale(locale);
    depositSumValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->ln_deposit_sum->setValidator(depositSumValidator);

    QIntValidator *timeValidator = new QIntValidator(0, 100, this);
    ui->ln_time->setValidator(timeValidator);

    QDoubleValidator *interestValidator = new QDoubleValidator(0.0, 100.0, 2, this);
    interestValidator->setLocale(locale);
    ui->ln_interest->setValidator(interestValidator);
    ui->ln_tax->setValidator(interestValidator);
}

Deposit::~Deposit() {
    delete ui;
}

deposit_model Deposit::set_model() {
    deposit_model model;
    model.deposit_sum = ui->ln_deposit_sum->text().toDouble();

    model.months = ui->ln_time->text().toDouble();
    if (ui->cmb_time->currentIndex() == 0) {
        model.months *= 12;
    }

    model.interest = ui->ln_interest->text().toDouble();
    model.tax = ui->ln_tax->text().toDouble();
    model.pay_freq_idx = ui->cmb_pay_freq->currentIndex();
    model.capitalization = ui->cb_capitalization->isChecked();
    int months = 12;

    QVariant itemData = ui->de_begin_date->date();
    QString dateString = itemData.toString();
    QDate begin_date = QDate::fromString(dateString, "yyyy-MM-dd");
    model.begin_date.tm_year = begin_date.year() - 1900;
    model.begin_date.tm_mon = begin_date.month() - 1;
    model.begin_date.tm_mday = begin_date.day();

    QDate end_date = begin_date.addMonths(months);
    model.days = begin_date.daysTo(end_date);
    model.sum_tax = 0;

    return model;
}

void Deposit::get_model(deposit_model model) {
    ui->lb_ac_interest_res->setText(QString::number(model.ac_interest, 'f', 2));
    ui->lb_sum_tax_res->setText(QString::number(model.sum_tax, 'f', 2));
    ui->lb_total_res->setText(QString::number(model.sum_total, 'f', 2));
}

QDate Deposit::getReplenishmentDate(int row) {
    QTableWidgetItem *dateItem = ui->tb_replenish_withdraw->item(row, 0);
    QDate date;
    if (dateItem) {
        QVariant itemData = dateItem->data(Qt::DisplayRole);
        QString dateString = itemData.toString();
        date = QDate::fromString(dateString, "dd.MM.yyyy");
    }
    return date;
}

double Deposit::getReplenishmentAmount(int row) {
    QTableWidgetItem *sumItem = ui->tb_replenish_withdraw->item(row, 1);
    double amount = 0;
    if (sumItem) {
        amount = sumItem->text().toDouble();
    }
    return amount;
}

void Deposit::s21_deposit(deposit_model *model) {
    model->ac_interest = 0;
    model->sum_tax = 0;
    model->sum_total = model->deposit_sum;

    double deposit_sum = ui->ln_deposit_sum->text().toDouble();
    double interest_rate = ui->ln_interest->text().toDouble();
    double remaining_balance = deposit_sum;
    double accrued_interest = 0;
    double prev_accrued_interest = 0;
    double period_interest = 0;
    int capitalization_freq = model->pay_freq_idx;

    QDate current_date = ui->de_begin_date->date();
    QDate begin_date = current_date;
    current_date = current_date.addDays(1);
    QDate end_date = current_date.addMonths(model->months);
    int replenish_row = 0;
    int prev_year = current_date.year();
    while (current_date < end_date) {
        int days_in_year = QDate::isLeapYear(current_date.year()) ? 366 : 365;
        double daily_interest = remaining_balance * (interest_rate / days_in_year) / 100.0;
        period_interest += round(daily_interest * 100.0) / 100.0;

        if (current_date.year() != prev_year) {
            calculate_tax(model, accrued_interest - prev_accrued_interest);
            prev_year = current_date.year();
            prev_accrued_interest += accrued_interest;
        }

        if (capitalization_freq == 0) { // Каждый день
            if (model->capitalization) remaining_balance += daily_interest;
            accrued_interest += period_interest;
            period_interest = 0;
        } else if (capitalization_freq == 1) { // Раз в месяц
            if (current_date.day() == begin_date.day()) {
                if (model->capitalization) remaining_balance += period_interest;
                accrued_interest += period_interest;
                period_interest = 0;
            }
        } else if (capitalization_freq == 2) { // Раз в квартал
            if (current_date.day() == begin_date.day() &&
                (current_date.month() == begin_date.month() || current_date.month() == (begin_date.month() + 3) % 12 ||
                 current_date.month() == (begin_date.month() + 6) % 12 ||
                 current_date.month() == (begin_date.month() + 9) % 12)) {
                if (model->capitalization) remaining_balance += period_interest;
                accrued_interest += period_interest;
                period_interest = 0;
            }
        } else if (capitalization_freq == 3) { // Раз в полгода
            if (current_date.day() == begin_date.day() &&
                (current_date.month() == begin_date.month() || current_date.month() == (begin_date.month() + 6) % 12)) {
                if (model->capitalization) remaining_balance += period_interest;
                accrued_interest += period_interest;
                period_interest = 0;
            }
        } else if (capitalization_freq == 4) { // Раз в год
            if (current_date.day() == begin_date.day() && current_date.month() == begin_date.month()) {
                if (model->capitalization) remaining_balance += period_interest;
                accrued_interest += period_interest;
                period_interest = 0;
            }
        } else if (capitalization_freq == 5) {
            QDate tmp_date = end_date.addDays(-1);
            if (current_date == tmp_date) {
                if (model->capitalization) remaining_balance += period_interest;
                accrued_interest += period_interest;
            }
        }

        if (replenish_row < ui->tb_replenish_withdraw->rowCount()) {
            while ((getReplenishmentDate(replenish_row) == current_date) &&
                   (replenish_row < ui->tb_replenish_withdraw->rowCount())) {
                double replenishment_amount = getReplenishmentAmount(replenish_row);
                remaining_balance += replenishment_amount;
                period_interest += replenishment_amount;
                model->sum_total += replenishment_amount;
                replenish_row++;
            }
        }

        current_date = current_date.addDays(1);
    }

    model->ac_interest = round(accrued_interest * 100) / 100;
    if (model->capitalization) model->sum_total += model->ac_interest;
}

void Deposit::calculate_tax(deposit_model *model, double interest) {
    double tax = model->tax;
    double taxfree = 1000000.0 * (tax / 100.0);
    double sum_tax = (interest - taxfree) * (13.0 / 100.0);
    if (sum_tax > 0) model->sum_tax += sum_tax;
}

void Deposit::on_pushButton_clicked() {
    ui->tb_replenish_withdraw->sortItems(0, Qt::AscendingOrder);
    deposit_model model = set_model();
    s21_deposit(&model);
    get_model(model);
}

void Deposit::on_bt_plus_clicked() {
    int new_row = ui->tb_replenish_withdraw->rowCount();
    ui->tb_replenish_withdraw->setRowCount(new_row + 1);
    QTableWidgetItem *it_date = new QTableWidgetItem;
    QTableWidgetItem *it_sum = new QTableWidgetItem;

    it_date->setText(QDate::currentDate().toString("dd.MM.yyyy"));
    it_date->setTextAlignment(Qt::AlignCenter);
    ui->tb_replenish_withdraw->setItem(new_row, 0, it_date);

    it_sum->setText("0");
    it_sum->setTextAlignment(Qt::AlignCenter);
    ui->tb_replenish_withdraw->setItem(new_row, 1, it_sum);
}

void Deposit::on_pushButton_Additions_minus_clicked() {
    ui->tb_replenish_withdraw->removeRow(ui->tb_replenish_withdraw->currentRow());
}

