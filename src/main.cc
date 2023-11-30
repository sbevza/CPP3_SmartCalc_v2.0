#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::ModelCredit modelCredit;
  s21::ModelDeposit modelDeposit;
  s21::Controller controller(&model, &modelCredit, &modelDeposit);

  MainWindow w(&controller);
  w.show();
  return a.exec();
}
