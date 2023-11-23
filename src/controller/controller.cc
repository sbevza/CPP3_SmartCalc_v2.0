#include "controller.h"

namespace s21 {

Controller::Controller(Model *model, ModelCredit *modelCredit, ModelDeposit *modelDeposit) :
    model_(model), modelCredit_(modelCredit), modelDeposit_(modelDeposit) {};

void Controller::convert_to_poland(std::string str_in, std::string str_out) {
  model_->convert_to_poland();
}

void Controller::handleInput(std::string str_in, double x) {
  model_->reset();
  model_->setModel(str_in, x);
  model_->convert_to_poland();
  model_->calculate();
}

int Controller::getErrorStatus() {
  return model_->getErrorStatus();
}

double Controller::getResult() {
  return model_->getResult();
}

void Controller::setCreditData(CreditData data) {
  modelCredit_->setModel(data);
}

void Controller::calculateCredit() {
  modelCredit_->calculate();
}

void Controller::calculateDeposit() {
  modelDeposit_->calculate();
}

CreditData Controller::getCreditData() {
  return modelCredit_->getResult();
}

DepositData Controller::getDepositData() {
  return modelDeposit_->getResult();
}

void Controller::setDepositData(DepositData data) {
  modelDeposit_->setModel(data);
}

//void Controller::reset() {
//  model->reset();
//}
}
