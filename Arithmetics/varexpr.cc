#include "varexpr.h"

using namespace std;

// Implementation of User-Defined Exception
VarNotSetException::VarNotSetException(): message{"Variable is not set!"} {}
VarNotSetException::VarNotSetException(const string &message): message{message} {}
string VarNotSetException::getMessage() { return message;}

VarExpr::VarExpr(const string &var): name{var} {
    this->isSet = false;
}

void VarExpr::set(const string &var, int num) {
    if (!var.empty() && var == this->name) {
        this->value = num;
        this->isSet = true;
    }
}

void VarExpr::unset(const string &var) {
    if (this->isSet && this->name == var) {
        this->value = 0;
        this->isSet = false;
    }
}

// Prints Variable name or Value if it is set
string VarExpr::prettyprint() {
    if (this->isSet) {
        return to_string(this->value);
    }
    else {
        return this->name;
    }
}

int VarExpr::evaluate() {
    if (this->isSet) {
        return this->value;
    } else {
        string message = this->name + " has no value.";
        throw VarNotSetException(message);
    }
}
