#ifndef UNARY_OP_EXPR_H
#define UNARY_OP_EXPR_H
#include "expr.h"

// Expression Class for Unary Operations
class UniOpExpr : public Expr {
private:
    Expr *expr;
    std::string op;

public:
    UniOpExpr(Expr *expr, const std::string &op);

    void set(const std::string &var, int num) override;

    void unset(const std::string &var) override;

    std::string prettyprint() override;

    int evaluate() override;

    ~UniOpExpr() override;
};
#endif
