#include "model_bak.h"

namespace s21 {
void Model::add(double a) {
  data += a;
}

void Model::mult(double a) {
  data *= a;
}

void Model::reset() {
  data = 0;
}

double Model::getData() {
  return data;
}
}