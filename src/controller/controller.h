#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model/model.h"

namespace s21 {
class Controller
{
    public:
        Controller(Model *m): model(m) {};
        void convert_to_poland(std::string str_in, std::string str_out);
        void handleInput(std::string str_in, double x);
        int getErrorStatus();
        double getResult();

        void setDepositData();

        struct DepositData {
          double deposit_sum;
          double months;
          double days;
          std::tm begin_date;
          std::tm end_date;
          double interest;
          double tax;
          int pay_freq_idx;
          int capitalization;
          double ac_interest;
          double sum_tax;
          double sum_total;
        };

    private:
        Model *model;
};
}
#endif
