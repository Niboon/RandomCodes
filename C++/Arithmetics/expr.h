#ifndef EXPR_H
#define EXPR_H
#include <string>
#include <iostream>

// Abstract Base Class for Expressions
class Expr {
public:
    virtual void set(const std::string &var, int num) = 0;
    virtual void unset(const std::string &var) = 0;
    virtual std::string prettyprint() = 0;
    virtual int evaluate() = 0;
    virtual ~Expr();
};
#endif
