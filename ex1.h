// Created by hilla on 18/11/2019.
//

#ifndef UNTITLED_EX1_H
#define UNTITLED_EX1_H
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <math.h>
#include <bits/stdc++.h>
#include "Expression.h"

using namespace std;

class Variable : public Expression {
private:
    string name;
    double value;
public:
    //constructor
    Variable(string n, double v);

    //destructor
    virtual ~Variable();

    Variable &operator++();

    Variable &operator--();

    Variable &operator+=(double increase);

    Variable &operator-=(double decrease);

    Variable &operator++(int);

    Variable &operator--(int);

    virtual double calculate();


};

class Value : public Expression {
private:
    mutable double value;

public:
    //constructor
    Value(double v);

    //destructor
    virtual ~Value();

    virtual double calculate();
};

class UnaryOperator : public Expression {
protected:
    Expression *exp;
public:
    //constructor
    UnaryOperator(Expression *expression);

    //destructor
    virtual ~UnaryOperator();
};

class UPlus : public UnaryOperator {

public:
    //constructor inheritance
    UPlus(Expression *expression);

    //destructor
    virtual ~UPlus();

    virtual double calculate();
};

class UMinus : public UnaryOperator {

public:
    //constructor inheritance
    UMinus(Expression *expression);

    //destructor
    virtual ~UMinus();

    virtual double calculate();


};

class BinaryOperator : public Expression {
protected:
    Expression *leftExp;
    Expression *rightExp;

public:
    //constructor
    BinaryOperator(Expression *left, Expression *right);

    //destructor
    virtual ~BinaryOperator();
};

class Plus : public BinaryOperator {

public:
    //constructor inheritance
    Plus(Expression *left, Expression *right);

    //destructor
    virtual ~Plus();

    virtual double calculate();


};

class Minus : public BinaryOperator {
public:
    //constructor inheritance
    Minus(Expression *left, Expression *right);

    //destructor
    virtual ~Minus();

    virtual double calculate();
};

class Mul : public BinaryOperator {
public:
    //constructor inheritance
    Mul(Expression *left, Expression *right);

    //destructor
    virtual ~Mul();

    virtual double calculate();
};

class Div : public BinaryOperator {
public:
    //constructor inheritance
    Div(Expression *left, Expression *right);

    //destructor
    virtual ~Div();

    virtual double calculate();
};

int precedenceOperators(char op);

class Interpreter {
    map<string, double> variables;
public:
    //constructor
    Interpreter();

    //destructor
    virtual ~Interpreter();

    bool isValidExpression(string s);

    bool isValidVariables(string s);

    void setVariables(string str);

    Expression *interpret(string infix);

    string convertToString(char *name);


    double convert(char *num);
};


#endif //UNTITLED_EX1_H
