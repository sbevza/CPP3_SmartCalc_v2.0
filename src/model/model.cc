#include "model.h"

namespace s21 {

void Model::s21_SmartCalc(const std::string &str_in, double x, double &res) {
  reset();
//  std::string str_out;
  setModel(str_in, x);
  convert_to_poland();
  calculate();
  res = getResult();
}

void Model::convert_to_poland() {
  validate();
  if (!error_) {
    error_ = checkLength();
  }
  if (!error_) {
    error_ = check_brackets();
  }
  if (!error_) {
    error_ = check_tigenometry();
  }
  if (!error_) {
    error_ = parse();
  }

}

void Model::validate() {
  unsigned long i = 0;
  int err = 0;
  while ((i < in_.length() && !err)) {
    if (in_[i] == ' ') {
      i++;
      continue;
    }
    if (in_[i] == 'x') {
      str_valid_ += 'x';
    } else if (in_[i] == 'c' && in_[i + 1] == 'o' && in_[i + 2] == 's') {
      str_valid_ += 'c';
      i += 2;
    } else if (in_[i] == 's' && in_[i + 1] == 'i' && in_[i + 2] == 'n') {
      str_valid_ += 's';
      i += 2;
    } else if (in_[i] == 't' && in_[i + 1] == 'a' && in_[i + 2] == 'n') {
      str_valid_ += 't';
      i += 2;
    } else if (in_[i] == 'a' && in_[i + 1] == 'c' && in_[i + 2] == 'o' &&
        in_[i + 3] == 's') {
      str_valid_ += 'o';
      i += 3;
    } else if (in_[i] == 'a' && in_[i + 1] == 's' && in_[i + 2] == 'i' &&
        in_[i + 3] == 'n') {
      str_valid_ += 'i';
      i += 3;
    } else if (in_[i] == 'a' && in_[i + 1] == 't' && in_[i + 2] == 'a' &&
        in_[i + 3] == 'n') {
      str_valid_ += 'a';
      i += 3;
    } else if (in_[i] == 's' && in_[i + 1] == 'q' && in_[i + 2] == 'r' &&
        in_[i + 3] == 't') {
      str_valid_ += 'q';
      i += 3;
    } else if (in_[i] == 'l' && in_[i + 1] == 'n') {
      str_valid_ += 'l';
      i++;
    } else if (in_[i] == 'l' && in_[i + 1] == 'o' && in_[i + 2] == 'g') {
      str_valid_ += 'g';
      i += 2;
    } else if (in_[i] == 'm' && in_[i + 1] == 'o' && in_[i + 2] == 'd') {
      str_valid_ += 'm';
      i += 2;
    } else if (in_[i] == '(' && (in_[i + 1] == '-' || in_[i + 1] == '+')) {
      str_valid_ += '(';
      str_valid_ += '0';
    } else if (i == 0 && in_[i] == '-') {
      str_valid_ += '0';
      str_valid_ += '-';
    } else if (i == 0 && in_[i] == '+') {
      str_valid_ += '0';
      str_valid_ += '+';
    } else if ((in_[i] >= 48 && in_[i] <= 57) &&
        (in_[i + 1] == '(' || in_[i + 1] == 'a' || in_[i + 1] == 'c' ||
            in_[i + 1] == 's' || in_[i + 1] == 't' || in_[i + 1] == 'l' ||
            in_[i + 1] == 'x')) {
      str_valid_ += in_[i];
      str_valid_ += '*';
    } else if ((in_[i] >= 40 && in_[i] <= 57) || (in_[i] <= '^')) {
      str_valid_ += in_[i];
    } else {
      err = 1;
    }
    i++;
  }
}

int Model::checkLength() {
  int len = str_valid_.length();
  return len > Model::buffer_ || len < 1;
}

int Model::check_brackets() {
  int count = 0;
  int err = 0;
  for (int i = 0; str_valid_[i] != '\0' && !err; i++) {
    if (str_valid_[i] == '(') {
      count++;
    } else if (str_valid_[i] == ')') {
      count--;
      if (count < 0) {
        err = 1;
      }
    }
  }
  if (count != 0 && !err) {
    err = 1;
  }
  return err;
}

int Model::check_tigenometry() {
  int err = 0;
  for (int i = 0; str_valid_[i] != '\0' && !err; i++) {
    if ((str_valid_[i] == 's' || str_valid_[i] == 'c' || str_valid_[i] == 't' || str_valid_[i] == 'o' ||
        str_valid_[i] == 'i' || str_valid_[i] == 'a' || str_valid_[i] == 'q' || str_valid_[i] == 'l' ||
        str_valid_[i] == 'g') &&
        str_valid_[i + 1] != '(')
      err = 1;
  }
  return err;
}

int Model::parse() {
  unsigned long i = 0;
  int err = 0;
  std::stack<char> st;
  while ((i < str_valid_.length()) && !err) {
    if ((str_valid_[i] == 'x') || (priorites(str_valid_[i]) == 0)) {
      out_ += str_valid_[i];
      if (priorites(str_valid_[i + 1]) != 0) {
        out_ += ' ';
      }
    } else if ((str_valid_[i] == '(') || (priorites(str_valid_[i]) == 4)) {
      st.push(str_valid_[i]);
    } else if (str_valid_[i] == ')') {
      while (st.top() != '(' && !err) {
        char c = st.top();
        st.pop();
        if (c == '\0')
          err = 1;
        else
          out_ += c;
      }
      st.pop();
    } else if (priorites(str_valid_[i]) == 2 || priorites(str_valid_[i]) == 3 ||
        priorites(str_valid_[i]) == 5) {
      if ((st.empty() ? 0 : priorites(st.top())) < priorites(str_valid_[i])) {
        st.push(str_valid_[i]);
      } else if ((st.empty() ? 0 :priorites(st.top())) >= priorites(str_valid_[i])) {
        while ((st.empty() ? 0 : priorites(st.top())) >= priorites(str_valid_[i])) {
          out_ += st.top();
          st.pop();
        }
        st.push(str_valid_[i]);
      }
    }
    i++;
  }

  while (st.size() != 0) {
    out_ += st.top();
    st.pop();
  }
  return err;
}

int Model::priorites(char c) {
  int priority = 0;
  if (c == 's' || c == 'c' || c == 't' || c == 'g' || c == 'l' || c == 'q' ||
      c == 'o' || c == 'i' || c == 'a' || c == '^') {
    priority = 4;
  } else if (c == '*' || c == '/' || c == 'm') {
    priority = 3;
  } else if (c == '-' || c == '+') {
    priority = 2;
  } else if (c == '(' || c == ')') {
    priority = 1;
  } else if ((c >= 48 && c <= 57) || c == 46) {
    priority = 0;
  } else if (c == '^') {
    priority = 5;
  }
  return priority;
}

int Model::calculate() {
  int err = 0, pointer = 0, i = 0;
  std::vector<double> st;
  while (out_.size() > i && !err) {
    if ((out_[i] >= 48 && out_[i] <= 57) || out_[i] == 46) {
      std::string num;
      while (((out_[i] >= 48 && out_[i] <= 57) || out_[i] == 46)) {
        num += out_[i++];
      }
      i--;
      err = check_dots(num);
      if (!err) {
        try {
          st.push_back(std::stod(num));
          pointer++;
        } catch (const std::invalid_argument &e) {
          err = 1;
        }
      }
    } else if (out_[i] == 'x') {
      st.push_back(x_);
      pointer++;
    } else if (out_[i] != ' ') {
      err = execute(out_[i], st, pointer);
    }
    i++;
  }

  if (!err && pointer == 1) {
    result_ = st[0];
  } else {
    err = 1;
  }
  error_ = error_ ? error_ : err;
  return err;
}

int Model::execute(char c, std::vector<double> &st, int &pointer) {
  int err = 0;
  err = check_pointer(c, pointer);
  if (!err) {
    switch (c) {
      case '+':st[pointer - 2] += st[pointer - 1];
        st.pop_back();
        (pointer)--;
        break;
      case '-':st[pointer - 2] -= st[pointer - 1];
        st.pop_back();
        (pointer)--;
        break;
      case '*':st[pointer - 2] *= st[pointer - 1];
        st.pop_back();
        (pointer)--;
        break;
      case '/':err = st[pointer - 1] == 0 ? 2 : 0;
        if (!err) {
          st[pointer - 2] /= st[pointer - 1];
          st.pop_back();
          (pointer)--;
        } else {
          error_ = err;
        }
        break;
      case 'm':st[pointer - 2] = fmod(st[pointer - 2], st[pointer - 1]);
        st.pop_back();
        (pointer)--;
        break;
      case 's':st[pointer - 1] = sin(st[pointer - 1]);
        break;
      case 'c':st[pointer - 1] = cos(st[pointer - 1]);
        break;
      case 't':st[pointer - 1] = tan(st[pointer - 1]);
        break;
      case 'o':st[pointer - 1] = acos(st[pointer - 1]);
        break;
      case 'i':st[pointer - 1] = asin(st[pointer - 1]);
        break;
      case 'a':st[pointer - 1] = atan(st[pointer - 1]);
        break;
      case 'q':st[pointer - 1] = sqrt(st[pointer - 1]);
        break;
      case 'l':st[pointer - 1] = log(st[pointer - 1]);
        break;
      case 'g':st[pointer - 1] = log10(st[pointer - 1]);
        break;
      case '^':st[pointer - 2] = pow(st[pointer - 2], st[pointer - 1]);
        st.pop_back();
        (pointer)--;
        break;
    }
  }
  return err;
}

int Model::check_pointer(char operation, int pointer) {
  int err = 0;
  if ((pointer < 2) &&
      (operation == '+' || operation == '-' || operation == '*' ||
          operation == '/' || operation == 'm' || operation == '^'))
    err = 1;
  else if ((pointer < 1) &&
      (operation == 's' || operation == 'c' || operation == 't' ||
          operation == 'o' || operation == 'i' || operation == 'a' ||
          operation == 'q' || operation == 'l' || operation == 'g'))
    err = 1;

  return err;
}

int Model::check_dots(const std::string &str) {
  int count = 0;
  size_t length = str.size();
  for (size_t i = 0; i < length; i++) {
    if (str[i] == '.') {
      count++;
    }
  }

  return count > 1;
}

void Model::setModel(const std::string &in, double x) {
  in_ = in;
  x_ = x;
}

void Model::reset() {
    in_.clear();
    out_.clear();
    str_valid_.clear();
    x_ = 0;
    error_ = 0;
    result_ = 0;
}

int Model::getErrorStatus() {
  return error_;
}

double Model::getResult() {
  return result_;
}

};
