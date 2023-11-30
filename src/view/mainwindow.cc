
#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "view/credit.h"
#include "view/deposit.h"

MainWindow::MainWindow(s21::Controller *c, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller(c) {
  ui->setupUi(this);
  double x_max = 10;
  double x_min = -10;
  double y_max = 10;
  double y_min = -10;
  ui->plot->xAxis->setRange(x_min, x_max);
  ui->plot->yAxis->setRange(y_min, y_max);
  ui->x_max_line->setText(QString::number(x_max));
  ui->x_min_line->setText(QString::number(x_min));
  ui->y_max_line->setText(QString::number(y_max));
  ui->y_min_line->setText(QString::number(y_min));
  ui->plot->setBackground(QColor(20, 20, 20));
  QCPAxis *xAxis = ui->plot->xAxis;
  QCPAxis *yAxis = ui->plot->yAxis;
  xAxis->setTickLabelColor(QColor(Qt::white));
  yAxis->setTickLabelColor(QColor(Qt::white));

  QLocale locale(QLocale::C);
  QDoubleValidator *dbValidator =
      new QDoubleValidator(-100000.0, 100000.0, 2, this);
  dbValidator->setLocale(locale);
  dbValidator->setNotation(QDoubleValidator::StandardNotation);
  ui->x_line->setValidator(dbValidator);

  QIntValidator *rangeValidator = new QIntValidator(-10000000, 10000000, this);
  ui->x_max_line->setValidator(rangeValidator);
  ui->x_min_line->setValidator(rangeValidator);
  ui->y_max_line->setValidator(rangeValidator);
  ui->y_max_line->setValidator(rangeValidator);

  //        QDoubleValidator *doubleValidator = new QDoubleValidator(0.0, 99.0,
  //        2, this);
  //          doubleValidator->setNotation(QDoubleValidator::StandardNotation);
  //          ui->percent->setValidator(doubleValidator);

  //    connect(ui->x_line, &QLineEdit::textChanged, [this]() {
  //            QString inputText = ui->x_line->text();
  //            int pos = 0;
  //            if (ui->x_line->validator()->validate(inputText, pos) !=
  //            QValidator::Acceptable) {
  //                ui->x_line->setStyleSheet("background-color: red;");
  //            } else {
  //                ui->x_line->setStyleSheet("");
  //            }
  //        });
  connect(ui->x_line, SIGNAL(textChanged(const QString &)), this,
          SLOT(on_x_line_textChanged(const QString &)));
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(operate_button()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(operate_button()));
  connect(ui->pushButton_bracket_l, SIGNAL(clicked()), this,
          SLOT(operate_button()));
  connect(ui->pushButton_bracket_r, SIGNAL(clicked()), this,
          SLOT(operate_button()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_x_line_textChanged(const QString &arg1) {
  QString inputText = arg1;
  int pos = 0;
  if (ui->x_line->validator()->validate(inputText, pos) !=
      QValidator::Acceptable) {
    ui->x_line->setStyleSheet("background-color: red;");
  } else {
    ui->x_line->setStyleSheet(
        "border: 1px solid white;\n	color: white;\n	font-family: "
        "Arial;\n	"
        "font-size: 14pt;\n	font-weight: 600;\n	margin-bottom: 4px;");
  }
}

void MainWindow::operate_button() {
  QPushButton *button = (QPushButton *)sender();
  ui->result_line->setText(ui->result_line->text() + button->text());
}

void MainWindow::on_pushButton_clear_all_clicked() {
  ui->result_line->setText("");
}

void MainWindow::on_pushButton_clear_clicked() {
  QString str = ui->result_line->text().chopped(1);
  ui->result_line->setText(str);
}

void MainWindow::on_pushButton_del_x_clicked() { ui->x_line->setText(""); }

void MainWindow::on_pushButton_result_clicked() {
  double x = ui->x_line->text().toDouble();
  std::string str = (ui->result_line->text()).toStdString();
  controller->handleInput(str, x);
  if (controller->getErrorStatus() == 0)
    ui->result_line->setText(QString::number(controller->getResult(), 'g', 15));
  else
    ui->result_line->setText("Error");
}

void MainWindow::on_pushButton_graph_clicked() {
  ui->plot->clearGraphs();
  x.clear();
  y.clear();

  QCPGraph *graph = ui->plot->addGraph();
  QPen pen;
  pen.setColor(Qt::red);  // Установка красного цвета
  graph->setPen(pen);
  //    ui->widget->graph(0)->setPen(QColor(143, 240, 164));
  //    graph->setLineStyle(QCPGraph::lsNone);
  //    graph->setScatterStyle(
  //    QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

  double x_max = ui->x_max_line->text().toDouble();
  double x_min = ui->x_min_line->text().toDouble();
  double y_max = ui->y_max_line->text().toDouble();
  double y_min = ui->y_min_line->text().toDouble();

  ui->plot->xAxis->setRange(x_min, x_max);
  ui->plot->yAxis->setRange(y_min, y_max);

  std::string str = (ui->result_line->text()).toStdString();

  int numPoints = 700;
  double delta = (x_max - x_min) / (numPoints - 1);
  if (delta > 0) {
    for (double i = x_min; i <= x_max && !controller->getErrorStatus();
         i += delta) {
      x.push_back(i);
      controller->handleInput(str, i);
      if (!controller->getErrorStatus()) y.push_back(controller->getResult());
      if (controller->getErrorStatus())
        qDebug() << controller->getErrorStatus();
    }
  }
  graph->addData(x, y);
  ui->plot->replot();
}

void MainWindow::on_pushButton_deposit_clicked() {
  Deposit window(controller);
  window.setModal(true);
  window.exec();
}

void MainWindow::on_pushButton_credit_clicked() {
  Credit window(controller);
  window.setModal(true);
  window.exec();
}
