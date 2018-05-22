#include "biopexpr.h"

using namespace std;

BiOpExpr::BiOpExpr(Expr *exprLeft, const string &op, Expr *exprRight) :
        exprLeft{exprLeft},
        exprRight{exprRight},
        op{op}
{}

void BiOpExpr::set(const string &var, int num) {
    this->exprLeft->set(var, num);
    this->exprRight->set(var, num);
}

void BiOpExpr::unset(const string &var) {
    this->exprLeft->unset(var);
    this->exprRight->unset(var);
}

string BiOpExpr::prettyprint() {
    return "(" +
            this->exprLeft->prettyprint() +
            " " +
            this->op +
            " " +
            this->exprRight->prettyprint() +
            ")";
}

int BiOpExpr::evaluate() {
    int ret = 0;
    if (this->op == "+") {
        ret = this->exprLeft->evaluate() + this->exprRight->evaluate();
    } else if (this->op == "-") {
        ret = this->exprLeft->evaluate() - this->exprRight->evaluate();
    } else if (this->op == "*") {
        ret = this->exprLeft->evaluate() * this->exprRight->evaluate();
    } else if (this->op == "/") {
        ret = this->exprLeft->evaluate() / this->exprRight->evaluate();
    }
    return ret;
}

BiOpExpr::~BiOpExpr() {
    delete exprLeft;
    delete exprRight;
}
