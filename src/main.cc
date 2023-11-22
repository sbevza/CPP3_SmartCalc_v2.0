#include "view/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  MainWindow w(&controller);
  w.show();
  return a.exec();

}
