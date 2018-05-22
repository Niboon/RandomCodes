#include <vector>
#include <iostream>
#include "uniopexpr.h"

using namespace std;


UniOpExpr::UniOpExpr(Expr *expr, const std::string &op): expr{expr}, op{op} {}

void UniOpExpr::set(const string &var, int num) {
    this->expr->set(var, num);
}

void UniOpExpr::unset(const string &var) {
    this->expr->unset(var);
}

string UniOpExpr::prettyprint() {
    string ret;
    if (this->op == "ABS") {
        ret = "|" + this->expr->prettyprint() + "|";
    } else if (this->op == "NEG") {
        ret = "-" + this->expr->prettyprint();
    }
    return ret;
}

int UniOpExpr::evaluate() {
    int ret = 0;
    if (this->op == "ABS") {
        ret = this->expr->evaluate();
        if (ret < 0) {
            ret *= -1;
        }
    } else if (this->op == "NEG") {
        ret = -1 * this->expr->evaluate();
    }
    return ret;
}

UniOpExpr::~UniOpExpr() {
    delete expr;
}
