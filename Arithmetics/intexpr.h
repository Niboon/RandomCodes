#ifndef INT_EXPR_H
#define INT_EXPR_H
#include "expr.h"

// Expression Class for Lone Integers
class IntExpr : public Expr {
private:
    int value;
public:
    explicit IntExpr(int num);

    void set(const std::string &var, int num) override;

    void unset(const std::string &var) override;

    std::string prettyprint() override;

    int evaluate() override;
};
#endif
