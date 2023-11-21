#include "view/mainwindow.h"
//#include "view/consoleView.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
//  s21::ConsoleView view(&controller);
//  view.startEventLoop();

  MainWindow w(&controller);
  w.show();
  return a.exec();

}
