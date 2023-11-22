#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDoubleValidator>
#include <QMainWindow>

#include "controller/controller.h"

QT_BEGIN_NAMESPACE
namespace s21 {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  s21::MainWindow *ui;
  QVector<double> x, y;
  s21::Controller *controller;

 private slots:
  void operate_button();
  void on_pushButton_clear_all_clicked();
  void on_pushButton_clear_clicked();
  void on_pushButton_del_x_clicked();
  void on_pushButton_result_clicked();
  void on_x_line_textChanged(const QString &arg1);
  void on_pushButton_graph_clicked();
  void on_pushButton_deposit_clicked();
  void on_pushButton_credit_clicked();
};

#endif  // MAINWINDOW_H
