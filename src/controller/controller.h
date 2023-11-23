#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model/model.h"
#include "model/model_credit.h"
#include "model/model_deposit.h"

namespace s21 {
class Controller
{
    public:
        Controller(Model *model, ModelCredit *modelCredit, ModelDeposit *modelDeposit);
        void convert_to_poland(std::string str_in, std::string str_out);
        void handleInput(std::string str_in, double x);
        void calculateCredit();
        void calculateDeposit();
        int getErrorStatus();
        double getResult();
        CreditData getCreditData();
        DepositData getDepositData();
        void setDepositData(DepositData data);
        void setCreditData(CreditData data);

    private:
        Model *model_;
        ModelCredit *modelCredit_;
        ModelDeposit *modelDeposit_;
};
}
#endif
