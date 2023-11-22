#ifndef MODEL_BAK_H
#define MODEL_BAK_H

namespace s21 {
class Model
{
    private:
        double data;
    public:
        Model():data(0){};
        void add(double a);
        void mult(double a);
        void reset();
        double getData();
};
}
#endif
