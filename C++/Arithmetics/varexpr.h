#ifndef VAR_EXPR_H
#define VAR_EXPR_H
#include "expr.h"

// User-Defined Exception for when VarExpr's value is not set
class VarNotSetException {
private:
    std::string message;
public:
    VarNotSetException();
    explicit VarNotSetException(const std::string &message);
    std::string getMessage();
};

// Expression Class for Variables
class VarExpr : public Expr {
private:
    std::string name;
    int value;
    bool isSet;

public:
    explicit VarExpr(const std::string &var);

    void set(const std::string &var, int num) override;

    void unset(const std::string &var) override;

    std::string prettyprint() override;

    int evaluate() override;

};
#endif
