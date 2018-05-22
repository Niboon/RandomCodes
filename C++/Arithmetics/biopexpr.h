#ifndef BINARY_OP_EXPR_H
#define BINARY_OP_EXPR_H
#include "expr.h"

// Expression Class for Binary Operations
class BiOpExpr : public Expr {
private:
    Expr *exprLeft;
    Expr *exprRight;
    std::string op;

public:
    BiOpExpr(Expr *exprLeft, const std::string &op, Expr *exprRight);

    void set(const std::string &var, int num) override;

    void unset(const std::string &var) override;

    std::string prettyprint() override;

    int evaluate() override;

    ~BiOpExpr() override;

};
#endif
