#include "controller.h"

namespace s21 {
void Controller::convert_to_poland(std::string str_in, std::string str_out){
  model->convert_to_poland();
}

void Controller::handleInput(std::string str_in, double x){
//    model->reset();
    model->setModel(str_in, x);
}

int Controller::getErrorStatus() {
  return model->getErrorStatus();
}

double Controller::getResult() {
    return model->getResult();
}

void Controller::setDepositData() {

}

//void Controller::reset() {
//  model->reset();
//}
}
