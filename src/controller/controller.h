#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model/model.h"

namespace s21 {
class Controller
{
    private:
        Model *model;
    public:
        Controller(Model *m): model(m) {};
        double add(double a);
        double sub(double a);
        double mult(double a);
        double div(double a);
        void reset();
};
}
#endif
