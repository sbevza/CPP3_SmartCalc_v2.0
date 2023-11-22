#include "model.h"

namespace s21 {

void Model::s21_SmartCalc(const std::string &str_in, double x, double &res) {
  std::string str_out;
  convert_to_poland();
//  calculate(str_out, x, res);
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
  int i = 0, i_out = 0, err = 0;
  while ((in_[i] != '\0' && !err)) {
    if (in_[i] == ' ') {
      i++;
      continue;
    }
    if (in_[i] == 'x') {
      out_[i_out++] = 'x';
    } else if (in_[i] == 'c' && in_[i + 1] == 'o' && in_[i + 2] == 's') {
      out_[i_out++] = 'c';
      i += 2;
    } else if (in_[i] == 's' && in_[i + 1] == 'i' && in_[i + 2] == 'n') {
      out_[i_out++] = 's';
      i += 2;
    } else if (in_[i] == 't' && in_[i + 1] == 'a' && in_[i + 2] == 'n') {
      out_[i_out++] = 't';
      i += 2;
    } else if (in_[i] == 'a' && in_[i + 1] == 'c' && in_[i + 2] == 'o' &&
               in_[i + 3] == 's') {
      out_[i_out++] = 'o';
      i += 3;
    } else if (in_[i] == 'a' && in_[i + 1] == 's' && in_[i + 2] == 'i' &&
               in_[i + 3] == 'n') {
      out_[i_out++] = 'i';
      i += 3;
    } else if (in_[i] == 'a' && in_[i + 1] == 't' && in_[i + 2] == 'a' &&
               in_[i + 3] == 'n') {
      out_[i_out++] = 'a';
      i += 3;
    } else if (in_[i] == 's' && in_[i + 1] == 'q' && in_[i + 2] == 'r' &&
               in_[i + 3] == 't') {
      out_[i_out++] = 'q';
      i += 3;
    } else if (in_[i] == 'l' && in_[i + 1] == 'n') {
      out_[i_out++] = 'l';
      i++;
    } else if (in_[i] == 'l' && in_[i + 1] == 'o' && in_[i + 2] == 'g') {
      out_[i_out++] = 'g';
      i += 2;
    } else if (in_[i] == 'm' && in_[i + 1] == 'o' && in_[i + 2] == 'd') {
      out_[i_out++] = 'm';
      i += 2;
    } else if (in_[i] == '(' && (in_[i + 1] == '-' || in_[i + 1] == '+')) {
      out_[i_out++] = '(';
      out_[i_out++] = '0';
    } else if (i == 0 && in_[i] == '-') {
      out_[i_out++] = '0';
      out_[i_out++] = '-';
    } else if (i == 0 && in_[i] == '+') {
      out_[i_out++] = '0';
      out_[i_out++] = '+';
    } else if ((in_[i] >= 48 && in_[i] <= 57) &&
               (in_[i + 1] == '(' || in_[i + 1] == 'a' || in_[i + 1] == 'c' ||
                in_[i + 1] == 's' || in_[i + 1] == 't' || in_[i + 1] == 'l' ||
                in_[i + 1] == 'x')) {
      out_[i_out++] = in_[i];
      out_[i_out++] = '*';
    } else if ((in_[i] >= 40 && in_[i] <= 57) || (in_[i] <= '^')) {
      out_[i_out++] = in_[i];
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
  int i = 0, i_out = 0, err = 0;
  std::stack<char> st;
  while ((in_[i] != '\0') && !err) {
    if ((in_[i] == 'x') || (priorites(in_[i]) == 0)) {
      out_[i_out++] = in_[i];
      if (priorites(in_[i + 1]) != 0) {
        out_[i_out++] = ' ';
      }
    } else if ((in_[i] == '(') || (priorites(in_[i]) == 4)) {
        st.push(in_[i]);
    } else if (in_[i] == ')') {
      while (st.top() != '(' && !err) {
        char c = st.top();
        st.pop();
        if (c == '\0')
          err = 1;
        else
          out_[i_out++] = c;
      }
      st.pop();
    } else if (priorites(in_[i]) == 2 || priorites(in_[i]) == 3 ||
               priorites(in_[i]) == 5) {
      if (priorites(st.top()) < priorites(in_[i])) {
        st.push(in_[i]);
      } else if (priorites(st.top()) >= priorites(in_[i])) {
        while (priorites(st.top()) >= priorites(in_[i])) {
            out_[i_out++] = st.top();
            st.pop();
        }
        st.push(in_[i]);
      }
    }
    i++;
  }

  while (st.size() != 0) {
    out_[i_out++] = st.top();
    st.pop();
  }
  return err;
}

int Model::priorites(char c) {
  int priority = 0;
  if (c == 's' || c == 'c' || c == 't' || c == 'g' || c == 'l' || c == 'q' ||
      c == 'o' || c == 'i' || c == 'a') {
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
  std::vector<double> st(buffer_, 0);
  while (out_[i] != '\0' && !err) {
    if ((out_[i] >= 48 && out_[i] <= 57) || out_[i] == 46) {
      std::string num(buffer_, '\0');
      int k = 0;
      while (((out_[i] >= 48 && out_[i] <= 57) || out_[i] == 46)) {
        num[k++] = out_[i++];
      }
      i--;
      err = check_dots(num);
      if (!err) {
//        st[pointer++] = atof(num);
        try {
                  st[pointer++] = std::stod(num);
                } catch (const std::invalid_argument& e) {
                  err = 1;
                }
      }
    } else if (out_[i] == 'x') {
      st[pointer++] = x_;
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
  return err;
}

int Model::execute(char c, std::vector<double> &st, int &pointer) {
  int err = 0;
  err = check_pointer(c, pointer);
  if (!err) {
    switch (c) {
      case '+':
        st[pointer - 2] += st[pointer - 1];
        (pointer)--;
        break;
      case '-':
        st[pointer - 2] -= st[pointer - 1];
        (pointer)--;
        break;
      case '*':
        st[pointer - 2] *= st[pointer - 1];
        (pointer)--;
        break;
      case '/':
        err = st[pointer - 1] == 0;
        if (!err) {
          st[pointer - 2] /= st[pointer - 1];
          (pointer)--;
        }
        break;
      case 'm':
        st[pointer - 2] = fmod(st[pointer - 2], st[pointer - 1]);
        (pointer)--;
        break;
      case 's':
        st[pointer - 1] = sin(st[pointer - 1]);
        break;
      case 'c':
        st[pointer - 1] = cos(st[pointer - 1]);
        break;
      case 't':
        st[pointer - 1] = tan(st[pointer - 1]);
        break;
      case 'o':
        st[pointer - 1] = acos(st[pointer - 1]);
        break;
      case 'i':
        st[pointer - 1] = asin(st[pointer - 1]);
        break;
      case 'a':
        st[pointer - 1] = atan(st[pointer - 1]);
        break;
      case 'q':
        st[pointer - 1] = sqrt(st[pointer - 1]);
        break;
      case 'l':
        st[pointer - 1] = log(st[pointer - 1]);
        break;
      case 'g':
        st[pointer - 1] = log10(st[pointer - 1]);
        break;
      case '^':
        st[pointer - 2] = pow(st[pointer - 2], st[pointer - 1]);
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

void Model::setModel(const std::string &in, double x){
    // Check length here !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    in_ = in;
    x_ = x;
}

int Model::getErrorStatus(){
    return error_;
}

double Model::getResult(){
    return result_;
}

};

//int check_dots(char *str) {
//  int count = 0;
//  size_t length = strlen(str);
//  for (size_t i = 0; i < length; i++) {
//    if (str[i] == '.') {
//      count++;
//    }
//  }

//  return count > 1;
//}



