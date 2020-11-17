#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <bits/stdc++.h>
#include <math.h>
#include "ex1.h"

using namespace std;

Variable::Variable(string n, double v) {
    this->name = n;
    this->value = v;
}

Variable &Variable::operator++() {
    this->value++;
    return *this;
}

Variable &Variable::operator--() {
    this->value--;
    return *this;
}

Variable &Variable::operator+=(double increase) {
    this->value += increase;
    return *this;
}

Variable &Variable::operator-=(double decrease) {
    this->value -= decrease;
    return *this;
}

Variable &Variable::operator++(int) {
    this->value++;
    return *this;
}

Variable &Variable::operator--(int) {
    this->value--;
    return *this;
}

double Variable::calculate() {
    return value;
}

Variable::~Variable() {

}

Value::Value(double v) {
    this->value = v;
}

double Value::calculate() {
    return this->value;
}

//destructor
Value::~Value() {

}

UnaryOperator::UnaryOperator(Expression *expression) {
    this->exp = expression;
}

UnaryOperator::~UnaryOperator() {
    delete exp;
}


UPlus::UPlus(Expression *expression) : UnaryOperator(expression) {}

double UPlus::calculate() {
    return this->exp->calculate();
}

UPlus::~UPlus() = default;

//constructor inheritance
UMinus::UMinus(Expression *expression) : UnaryOperator(expression) {

}

double UMinus::calculate() {
    return -(this->exp->calculate());
}

//destructor
UMinus::~UMinus() = default;

//constructor
BinaryOperator::BinaryOperator(Expression *left, Expression *right) {
    this->leftExp = left;
    this->rightExp = right;
}

//destructor
BinaryOperator::~BinaryOperator() {
    delete leftExp;
    delete rightExp;
}

//constructor inheritance
Plus::Plus(Expression *left, Expression *right) : BinaryOperator(left, right) {

}

double Plus::calculate() {
    return this->leftExp->calculate() + this->rightExp->calculate();
}

//destructor
Plus::~Plus() = default;

//constructor inheritance
Minus::Minus(Expression *left, Expression *right) : BinaryOperator(left, right) {

}

double Minus::calculate() {
    return this->leftExp->calculate() - this->rightExp->calculate();
}

//destructor
Minus::~Minus() = default;


Mul::Mul(Expression *left, Expression *right) : BinaryOperator(left, right) {

}

double Mul::calculate() {
    return this->leftExp->calculate() * this->rightExp->calculate();
}

Mul::~Mul() = default;


//constructor inheritance
Div::Div(Expression *left, Expression *right) : BinaryOperator(left, right) {
    if (right->calculate() == 0) {
        throw ("division by zero");
    }
}

double Div::calculate() {
    return this->leftExp->calculate() / this->rightExp->calculate();
}

//destructor
Div::~Div() = default;

//function return the Associativity of the operators
int precedenceOperators(char op) {
    if (op == '-' || op == '+' || op == '&' || op == '$')
        return 1;
    else if (op == '/' || op == '*')
        return 2;

    else if (op == '(')
        return 0;
        //op == ')'
    else
        return 4;
}

//constructor
Interpreter::Interpreter() {

}

bool Interpreter::isValidExpression(string s) {
    string str = "";
    string variable = "";
    int j = 0;
    bool k;
    for (unsigned int i = 0; i < s.length(); ++i) {
        str = str + s[i];
    }

    if (str[0] == '*' || str[0] == '/') {
        return false;
    }
    while (str[j] != '\0') {
        if (str[j] == '>') {

            j++;
            continue;

        } else if (!(str[j] >= '0' && str[j] <= '9') && str[j] != '.' &&
                   !((str[j] >= 'a' && str[j] <= 'z') || (str[j] >= 'A' && str[j] <= 'Z')) &&
                   str[j] != '(' && str[j] != ')' && str[j] != '+' && str[j] != '-' &&
                   str[j] != '*' && str[j] != '/') {
            return false;
        } else if ((str[j] >= 'a' && str[j] <= 'z') || (str[j] >= 'A' && str[j] <= 'Z')) {
            while ((str[j] == '_' || (str[j] >= '0' && str[j] <= '9') ||
                    ((str[j] >= 'a' && str[j] <= 'z') || (str[j] >= 'A' && str[j] <= 'Z')))
                   && str[j] != '>') {
                variable = variable + str[j];
                j++;
            }
            if (variables.find(variable) == variables.end()) {
                return false;
            }
            variable = "";

        } else if (str[j] == '(') {

            for (unsigned int i = j + 1; i < str.length(); ++i) {
                k = (str[i] == ')');
                if (k) {
                    str[j] = '>';
                    str[i] = '>';
                    break;
                }
            }
            if (!k) {
                return false;
            }

        } else if (str[j] == ')') {
            return false;
        } else if ((str[j] == '+' || str[j] == '-' || str[j] == '*' || str[j] == '/')
                   && (str[j + 1] == '+' || str[j + 1] == '-' || str[j + 1] == '*' || str[j + 1] == '/')) {
            return false;

        } else if (str[str.length() - 1] == '+' || str[str.length() - 1] == '-'
                   || str[str.length() - 1] == '*' || str[str.length() - 1] == '/') {
            return false;
        }
        j++;
    }
    return true;
}

bool Interpreter::isValidVariables(string s) {
    unsigned int find;
    bool run = true;
    string str = "";
    for (unsigned int i = 0; i < s.length(); ++i) {
        str = str + s[i];
    }

    while (run) {
        find = str.find("=");
        if (!(str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')) {
            return false;
        }
        for (unsigned int j = 1; j < find; ++j) {
            if (str[j] != '_' && !(str[j] >= '0' && str[j] <= '9') &&
                !((str[j] >= 'a' && str[j] <= 'z') || (str[j] >= 'A' && str[j] <= 'Z'))) {
                return false;
            }
        }
        str.erase(0, find + 1);
        find = str.find(";");
        if (find > str.length()) {
            find = str.length();
            run = false;
        }
        for (unsigned int j = 0; j < find; ++j) {
            if (!((str[j] >= '0' && str[j] <= '9') || str[j] == '.')) {
                return false;
            }
        }
        str.erase(0, find + 1);
    }
    return true;
}

void Interpreter::setVariables(string str) {
    char *variableName, *value;
    bool run = true;
    int k = 0, i = 0;
    unsigned int find;
    if (!isValidVariables(str)) {
        throw ("illegal variable assignment!");
    }

    while (run) {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
            find = str.find("=");
            variableName = (char *) malloc(sizeof(char) * find + 1);
            for (unsigned int j = i; j < find; ++j) {
                variableName[k] = str[j];
                k++;
            }
            variableName[k] = '\0';
            k = 0;
            i = find + 1;
            find = str.find(";");
            if (find > str.length() ) {
                find = str.length();
            }
            value = (char *) malloc(sizeof(char) * find + 1);
            for (unsigned int j = i; j < find; ++j) {
                value[k] = str[i];
                i++;
                k++;
            }
            value[k] = '\0';
            str.erase(0, find + 1);
            i = 0;
            k = 0;
            variables[convertToString(variableName)] = convert(value);
        } else {
            run = false;
        }
    }

}


Expression *Interpreter::interpret(string infix) {
    queue<char *> numbers;
    queue<char *> opReplace;
    stack<Expression *> numbersNew;
    stack<char *> operators;
     int j, k = 0;
    char *num, *op;
    if (!isValidExpression(infix)) {
        throw ("illegal math expression");
    }
    for ( int i = 0; infix[i] != '\0'; ++i) {
        j = i + 1;
        k = 0;
        num = (char *) malloc(sizeof(char) * infix.length());
        if (infix[i] >= '0' && infix[i] <= '9') {
            num[k] = infix[i];
            while ((infix[j] >= '0' && infix[j] <= '9') || infix[j] == '.') {
                k++;
                num[k] = infix[j];
                i = j;
                j++;
            }
            num[k + 1] = '\0';
            numbers.push(num);
        } else if ((infix[i] >= 'a' && infix[i] <= 'z') ||
                   (infix[i] >= 'A' && infix[i] <= 'Z')) {
            num[k] = infix[i];
            while (infix[j] != '+' && infix[j] != '-' && infix[j] != '*'
                   && infix[j] != '/' && infix[j] != '(' && infix[j] != ')') {
                k++;
                num[k] = infix[j];
                i = j;
                j++;
            }
            num[k + 1] = '\0';
            numbers.push(num);
        } else {
            op = (char *) malloc(sizeof(char) * 1);
            *op = infix[i];
            if (*op == '+' && (infix[i - 1] == '(' || i == 0)) {
                *op = '$';
            }
            if (*op == '-' && (infix[i - 1] == '(' || i == 0)) {
                *op = '&';
            }
            if (operators.empty() ||
                ((precedenceOperators(*operators.top()) < precedenceOperators(*op) &&
                  precedenceOperators(*op) != 4)
                 || precedenceOperators(*op) == 0)) {
                operators.push(op);
            } else if (precedenceOperators(*op) == 4) {
                while (*operators.top() != '(') {
                    numbers.push(operators.top());
                    operators.pop();
                }
                free(op);
                free(operators.top());
                operators.pop();
            } else {
                while ((!operators.empty()) &&
                       (precedenceOperators(*operators.top()) >= precedenceOperators(*op))) {
                    numbers.push(operators.top());
                    operators.pop();
                }
                operators.push(op);
            }
        }
    }
    while (!operators.empty()) {
        numbers.push(operators.top());
        operators.pop();
    }
    //now the numbers queue contains the postfix order
    Expression *left, *right, *unary;
    while (!numbers.empty()) {
        if (*numbers.front() >= '0' && *numbers.front() <= '9') {
            Expression *e = new Value(this->convert(numbers.front()));
            free(numbers.front());
            numbers.pop();
            numbersNew.push(e);
        } else if ((*numbers.front() >= 'a' && *numbers.front() <= 'z') ||
                   (*numbers.front() >= 'A' && *numbers.front() <= 'Z')) {
            string s = convertToString(numbers.front());
            Expression *e = new Variable(numbers.front(), this->variables[s]);
            free(numbers.front());
            numbers.pop();
            numbersNew.push(e);
        } else if (*numbers.front() == '-') {
            free(numbers.front());
            numbers.pop();
            left = numbersNew.top();
            numbersNew.pop();
            right = numbersNew.top();
            numbersNew.pop();
            Expression *e = new Minus(right, left);
            numbersNew.push(e);


        } else if (*numbers.front() == '+') {
            free(numbers.front());
            numbers.pop();
            left = numbersNew.top();
            numbersNew.pop();
            right = numbersNew.top();
            numbersNew.pop();
            Expression *e = new Plus(left, right);
            numbersNew.push(e);
        } else if (*numbers.front() == '*') {
            free(numbers.front());
            numbers.pop();
            left = numbersNew.top();
            numbersNew.pop();
            right = numbersNew.top();
            numbersNew.pop();
            Expression *e= new Mul(left, right);
            numbersNew.push(e);

        } else if (*numbers.front() == '/') {
            free(numbers.front());
            numbers.pop();
            left = numbersNew.top();
            numbersNew.pop();
            right = numbersNew.top();
            numbersNew.pop();
            Expression *e = new Div(left, right);
            numbersNew.push(e);
        } else if (*numbers.front() == '$') {
            free(numbers.front());
            numbers.pop();
            unary = new UPlus(numbersNew.top());
            numbersNew.pop();
            numbersNew.push(unary);
        } else if (*numbers.front() == '&') {
            free(numbers.front());
            numbers.pop();
            unary = new UMinus(numbersNew.top());
            numbersNew.pop();
            numbersNew.push(unary);
        }
    }

    Expression *e = numbersNew.top();
    numbersNew.pop();
    return e;
}

string Interpreter::convertToString(char *name) {
    string variableName = "";
    int i;
    for (i = 0; name[i] != '\0'; ++i) {
        variableName = variableName + name[i];
    }
    return variableName;
}


double Interpreter::convert(char *num) {
    double n = 0;
    int point = 0, length = 0, j = 0;
    for (int i = 0; num[i] != '\0'; ++i) {
        if (num[i] == '.') {
            point = i;
        }
        length++;
    }
    if (point == 0) {
        j = length - 1;
        for (int i = 0; i < length; ++i) {
            n += ((int) num[i] - 48) * pow(10, j);
            j--;
        }
        return n;
    }
    j = point - 1;
    for (int i = 0; i < point; ++i) {
        n += ((int) num[i] - 48) * pow(10, j);
        j--;
    }
    j = length - (point + 1);

    for (int i = length - 1; i != point; --i) {
        n += ((int) num[i] - 48) * pow(10, -j);
        j--;
    }
    return n;
}

//destructor
Interpreter::~Interpreter() {}





