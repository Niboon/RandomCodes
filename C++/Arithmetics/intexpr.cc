#include <vector>
#include <iostream>
#include "intexpr.h"

using namespace std;

IntExpr::IntExpr(int num): value{num} {}

void IntExpr::set(const string &var, int num) {
    // no-opt
}

void IntExpr::unset(const string &var) {
    // no-opt
}

string IntExpr::prettyprint() {
    return to_string(value);
}

int IntExpr::evaluate() {
    return value;
}
