#include "s21_SmartCalc.h"

//#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

int check_length(const char *str) {
  int len = (int)strlen(str);
  return len > BUFFER || len < 1;
}

stack create_stack() {
  stack st;
  st.top = 0;
  char str_out[BUFFER] = {'\0'};
  strcpy(st.elements, str_out);
  return st;
}

int s21_SmartCalc(const char *str_in, double x, double *res) {
  int err = 0;
  char str_out[BUFFER] = {0};
  err = convert_to_poland(str_in, str_out);
  if (!err) {
    err = calculate(str_out, x, res);
  }
  return err;
}

int calculate(const char *in, double x, double *res) {
  int err = 0, pointer = 0, i = 0;
  double st[BUFFER] = {0};
  while (in[i] != '\0' && !err) {
    if ((in[i] >= 48 && in[i] <= 57) || in[i] == 46) {
      char num[BUFFER] = {'\0'};
      int k = 0;
      while (((in[i] >= 48 && in[i] <= 57) || in[i] == 46)) {
        num[k++] = in[i++];
      }
      i--;
      err = check_dots(num);
      if (!err) {
        st[pointer++] = atof(num);
      }
    } else if (in[i] == 'x') {
      st[pointer++] = x;
    } else if (in[i] != ' ') {
      err = execute(in[i], st, &pointer);
    }
    i++;
  }

  if (!err && pointer == 1) {
    *res = st[0];
  } else {
    err = 1;
  }
  return err;
}

int check_dots(char *str) {
  int count = 0;
  size_t length = strlen(str);
  for (size_t i = 0; i < length; i++) {
    if (str[i] == '.') {
      count++;
    }
  }

  return count > 1;
}

int check_pointer(char operation, int pointer) {
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

int execute(char c, double *st, int *pointer) {
  int err = 0;
  err = check_pointer(c, *pointer);
  if (!err) {
    switch (c) {
      case '+':
        st[*pointer - 2] += st[*pointer - 1];
        (*pointer)--;
        break;
      case '-':
        st[*pointer - 2] -= st[*pointer - 1];
        (*pointer)--;
        break;
      case '*':
        st[*pointer - 2] *= st[*pointer - 1];
        (*pointer)--;
        break;
      case '/':
        err = st[*pointer - 1] == 0;
        if (!err) {
          st[*pointer - 2] /= st[*pointer - 1];
          (*pointer)--;
        }
        break;
      case 'm':
        st[*pointer - 2] = fmod(st[*pointer - 2], st[*pointer - 1]);
        (*pointer)--;
        break;
      case 's':
        st[*pointer - 1] = sin(st[*pointer - 1]);
        break;
      case 'c':
        st[*pointer - 1] = cos(st[*pointer - 1]);
        break;
      case 't':
        st[*pointer - 1] = tan(st[*pointer - 1]);
        break;
      case 'o':
        st[*pointer - 1] = acos(st[*pointer - 1]);
        break;
      case 'i':
        st[*pointer - 1] = asin(st[*pointer - 1]);
        break;
      case 'a':
        st[*pointer - 1] = atan(st[*pointer - 1]);
        break;
      case 'q':
        st[*pointer - 1] = sqrt(st[*pointer - 1]);
        break;
      case 'l':
        st[*pointer - 1] = log(st[*pointer - 1]);
        break;
      case 'g':
        st[*pointer - 1] = log10(st[*pointer - 1]);
        break;
      case '^':
        st[*pointer - 2] = pow(st[*pointer - 2], st[*pointer - 1]);
        (*pointer)--;
        break;
    }
  }
  return err;
}

int check_brackets(const char *str) {
  int count = 0;
  int err = 0;
  for (int i = 0; str[i] != '\0' && !err; i++) {
    if (str[i] == '(') {
      count++;
    } else if (str[i] == ')') {
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

int check_tigenometry(const char *str) {
  int err = 0;
  for (int i = 0; str[i] != '\0' && !err; i++) {
    if ((str[i] == 's' || str[i] == 'c' || str[i] == 't' || str[i] == 'o' ||
         str[i] == 'i' || str[i] == 'a' || str[i] == 'q' || str[i] == 'l' ||
         str[i] == 'g') &&
        str[i + 1] != '(')
      err = 1;
  }
  return err;
}

int convert_to_poland(const char *in, char *out) {
  int err = 0;
  char str_valid[BUFFER] = {0};
  err = validate(in, str_valid);
  if (!err) {
    err = check_length(str_valid);
  }
  if (!err) {
    err = check_brackets(str_valid);
  }
  if (!err) {
    err = check_tigenometry(str_valid);
  }
  if (!err) {
    err = parse(str_valid, out);
  }
  return err;
}

int parse(char *in, char *out) {
  int i = 0, i_out = 0, err = 0;
  stack st = create_stack();
  while ((in[i] != '\0') && !err) {
    if ((in[i] == 'x') || (priorites(in[i]) == 0)) {
      out[i_out++] = in[i];
      if (priorites(in[i + 1]) != 0) {
        out[i_out++] = ' ';
      }
    } else if ((in[i] == '(') || (priorites(in[i]) == 4)) {
      err = push(&st, in[i]);
    } else if (in[i] == ')') {
      while (peek(&st) != '(' && !err) {
        char c = pop(&st);
        if (c == '\0')
          err = 1;
        else
          out[i_out++] = c;
      }
      pop(&st);
    } else if (priorites(in[i]) == 2 || priorites(in[i]) == 3 ||
               priorites(in[i]) == 5) {
      if (priorites(peek(&st)) < priorites(in[i])) {
        err = push(&st, in[i]);
      } else if (priorites(peek(&st)) >= priorites(in[i])) {
        while (priorites(peek(&st)) >= priorites(in[i])) {
          out[i_out++] = pop(&st);
        }
        push(&st, in[i]);
      }
    }
    i++;
  }
  while (st.top != 0) {
    out[i_out++] = pop(&st);
  }
  return err;
}

int validate(const char *in, char out[BUFFER]) {
  int i = 0, i_out = 0, err = 0;
  while ((in[i] != '\0' && !err)) {
    if (in[i] == ' ') {
      i++;
      continue;
    }
    if (in[i] == 'x') {
      out[i_out++] = 'x';
    } else if (in[i] == 'c' && in[i + 1] == 'o' && in[i + 2] == 's') {
      out[i_out++] = 'c';
      i += 2;
    } else if (in[i] == 's' && in[i + 1] == 'i' && in[i + 2] == 'n') {
      out[i_out++] = 's';
      i += 2;
    } else if (in[i] == 't' && in[i + 1] == 'a' && in[i + 2] == 'n') {
      out[i_out++] = 't';
      i += 2;
    } else if (in[i] == 'a' && in[i + 1] == 'c' && in[i + 2] == 'o' &&
               in[i + 3] == 's') {
      out[i_out++] = 'o';
      i += 3;
    } else if (in[i] == 'a' && in[i + 1] == 's' && in[i + 2] == 'i' &&
               in[i + 3] == 'n') {
      out[i_out++] = 'i';
      i += 3;
    } else if (in[i] == 'a' && in[i + 1] == 't' && in[i + 2] == 'a' &&
               in[i + 3] == 'n') {
      out[i_out++] = 'a';
      i += 3;
    } else if (in[i] == 's' && in[i + 1] == 'q' && in[i + 2] == 'r' &&
               in[i + 3] == 't') {
      out[i_out++] = 'q';
      i += 3;
    } else if (in[i] == 'l' && in[i + 1] == 'n') {
      out[i_out++] = 'l';
      i++;
    } else if (in[i] == 'l' && in[i + 1] == 'o' && in[i + 2] == 'g') {
      out[i_out++] = 'g';
      i += 2;
    } else if (in[i] == 'm' && in[i + 1] == 'o' && in[i + 2] == 'd') {
      out[i_out++] = 'm';
      i += 2;
    } else if (in[i] == '(' && (in[i + 1] == '-' || in[i + 1] == '+')) {
      out[i_out++] = '(';
      out[i_out++] = '0';
    } else if (i == 0 && in[i] == '-') {
      out[i_out++] = '0';
      out[i_out++] = '-';
    } else if (i == 0 && in[i] == '+') {
      out[i_out++] = '0';
      out[i_out++] = '+';
    } else if ((in[i] >= 48 && in[i] <= 57) &&
               (in[i + 1] == '(' || in[i + 1] == 'a' || in[i + 1] == 'c' ||
                in[i + 1] == 's' || in[i + 1] == 't' || in[i + 1] == 'l' ||
                in[i + 1] == 'x')) {
      out[i_out++] = in[i];
      out[i_out++] = '*';
    } else if ((in[i] >= 40 && in[i] <= 57) || (in[i] <= '^')) {
      out[i_out++] = in[i];
    } else {
      err = 1;
    }
    i++;
  }
  return err;
}

int priorites(char c) {
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

char pop(stack *stack) {
  char val;
  if (stack->top == 0) {
    printf("Stack underflow!\n");
    val = '\0';
  } else {
    val = stack->elements[stack->top - 1];
    stack->top--;
  }

  return val;
}

int push(stack *stack, char val) {
  int err = 0;
  if (stack->top >= BUFFER) {
    printf("Stack overflow!\n");
    err = 1;
  } else {
    stack->elements[stack->top] = val;
    stack->top++;
  }
  return err;
}

char peek(stack *stack) {
  return (stack->top == 0) ? '\0' : stack->elements[stack->top - 1];
}
