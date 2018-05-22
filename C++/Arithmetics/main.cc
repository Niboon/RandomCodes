#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "intexpr.h"
#include "varexpr.h"
#include "uniopexpr.h"
#include "biopexpr.h"


using namespace std;

// You will need to make changes to this file

// Read and construct expression object.  Returns a pointer to a heap-allocated
// object (caller must delete it).
istream &operator>>(istream &in, Expr *&e) {
    string s;
    vector<Expr *> stack;
    while (cin >> s) {
        istringstream ss(s);
        int n;
        if (ss >> n) {
            stack.emplace_back(new IntExpr{n});
        }
        else if (s == "NEG" || s == "ABS") {
            Expr *popped = stack.back();
            stack.pop_back();
            stack.emplace_back(new UniOpExpr{popped, s});
        }
        else if (s == "+" || s == "-" || s == "*" || s == "/") {
            Expr *poppedRight = stack.back();
            stack.pop_back();
            Expr *poppedLeft = stack.back();
            stack.pop_back();
            stack.emplace_back(new BiOpExpr{poppedLeft, s, poppedRight});
        }
        else if (s == "done") {
            e = stack.back();
            break;
        }
        else {
            stack.emplace_back(new VarExpr{s});
        }
    }
    return in;
}

int main () {
    string s;

    Expr *e;
    cin >> e;
    const string &str = e->prettyprint();
    cout << str << endl;

    // Command interpreter
    while (cin >> s) {
        if (s == "eval") {
            try {
                cout << e->evaluate() << endl;
            } catch (VarNotSetException &e) {
                cout << e.getMessage() << endl;
            }
        }
        else if (s == "set") {
            cin >> s;
            int n;
            cin >> n;
            e->set(s, n);
        }
        else if (s == "unset") {
            cin >> s;
            e->unset(s);
        }
        else if (s == "print") {
            cout << e->prettyprint() << endl;
        }
    }
    delete e;
}
