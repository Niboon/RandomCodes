#include <iostream>
#include "polynomial.h"

using namespace std;

Polynomial::Polynomial(){   //creates the 0 polynomial
    this->coeffs = new Rational[1];    // initialize array with size of one
    this->capacity = 0;
}

Polynomial::Polynomial(const Rational &coeff, int exp) {  // Creates a monomial
    this->coeffs = new Rational[exp+1];
    this->capacity = exp+1;
    this->coeffs[exp] = coeff;
}

//Big five
// Destructor
Polynomial::~Polynomial() {
    delete[] this->coeffs;
}

// Copy Constructor
Polynomial::Polynomial(const Polynomial &other):
        capacity{other.capacity}
{
    if (other.capacity == 0) {
        this->coeffs = nullptr;
    } else {
        this->coeffs = new Rational[other.capacity];
        for (int i = 0; i < other.capacity; ++i) {
            this->coeffs[i] = other.coeffs[i];
        }
    }
}

// Move Constructor
Polynomial::Polynomial(Polynomial &&other):
        coeffs{other.coeffs},
        capacity{other.capacity}
{
    other.coeffs = nullptr;
}

// Copy Assignment
Polynomial &Polynomial::operator=(const Polynomial &other) {
    if (this->coeffs != other.coeffs) {
        Rational *temp = this->coeffs;
        if (other.capacity == 0) {
            this->coeffs = nullptr;
            this->capacity = other.capacity;
        } else {
            this->coeffs = new Rational[other.capacity];
            this->capacity = other.capacity;
            for (int i = 0; i < other.capacity; ++i) {
                this->coeffs[i] = other.coeffs[i];
            }
        }
        delete temp;
    }
    return *this;
}

// Move Assignment
Polynomial &Polynomial::operator=(Polynomial &&other){
    Rational *temp = this->coeffs;
    this->coeffs = other.coeffs;
    this->capacity = other.capacity;
    other.coeffs = temp;
    return *this;
}

// Arithmetic operations behave in the standard way
Polynomial Polynomial::operator+(const Polynomial &rhs) const{
    if (this->capacity >= rhs.capacity) {
        Polynomial ret{*this}; // Copy Larger Polynomial
        for (int i = 0; i < rhs.capacity; ++i) { // Loop Over Smaller Polynomial
            ret.coeffs[i] = this->coeffs[i] + rhs.coeffs[i];
        }
        return ret;
    } else {
        Polynomial ret{rhs}; // Copy Larger Polynomial
        for (int i = 0; i < this->capacity; ++i) { // Loop Over Smaller Polynomial
            ret.coeffs[i] = this->coeffs[i] + rhs.coeffs[i];
        }
        return ret;
    }
}

Polynomial Polynomial::operator-(const Polynomial &rhs) const{
    if (this->capacity >= rhs.capacity) {
        Polynomial ret{*this}; // Copy Larger Polynomial
        for (int i = 0; i < this->capacity; ++i) { // Loop Over Larger Polynomial
            if (i < rhs.capacity) {
                ret.coeffs[i] = this->coeffs[i] - rhs.coeffs[i];
            }
        }
        return ret;
    } else {
        Polynomial ret{rhs}; // Copy Larger Polynomial
        for (int i = 0; i < rhs.capacity; ++i) { // Loop Over Larger Polynomial
            if (i < this->capacity) {
                ret.coeffs[i] = this->coeffs[i] - rhs.coeffs[i];
            } else {
                ret.coeffs[i] = -ret.coeffs[i];
            }
        }
        return ret;
    }
}

Polynomial Polynomial::operator*(const Polynomial &rhs) const{
    int exp = this->capacity + rhs.capacity;
    Polynomial ret = Polynomial(Rational(), exp);
    for (int i = 0; i < rhs.capacity; ++i) {
        for (int j = 0; j < this->capacity; ++j) {
            ret.coeffs[i+j] += rhs.coeffs[i] * this->coeffs[j];
        }
    }
    return ret;
}


//returns quotient after long division
Polynomial Polynomial::operator/(const Polynomial &rhs) const{
    Polynomial remainder{*this};
    int exp = this->degree() - rhs.degree();
    if (exp <= 0) return Polynomial{};
    Polynomial quotient{Rational(), exp};
    for (int e=exp, j=this->degree(); e >= 0; --e, --j) {
        Rational mult = remainder.coeffs[j] / rhs.coeffs[rhs.degree()];
        quotient.coeffs[e] = mult;
        remainder = Polynomial(remainder - (rhs * Polynomial(mult, e)));
    }
    return quotient;
}


//returns remainder after long division
Polynomial Polynomial::operator%(const Polynomial &rhs) const{
    Polynomial remainder{*this};
    int exp = this->degree() - rhs.degree();
    if (exp <= 0) return remainder;
    Polynomial quotient{Rational(), exp};
    for (int e=exp, j=this->degree(); e >= 0; --e, --j) {
            Rational mult = remainder.coeffs[j] / rhs.coeffs[rhs.degree()];
            quotient.coeffs[e] = mult;
            remainder = Polynomial(remainder - (rhs * Polynomial(mult, e)));
    }
    return remainder;
}


// degree of the zero polynomial is -1
int Polynomial::degree() const{
    return (this->capacity - 1);
}


// Print with decreasing exponents.
std::ostream& operator<<(std::ostream& out, const Polynomial &poly){
    if (poly.capacity == 0 || !poly.coeffs) {
        out << 0;
        return out;
    }
    bool doPrefix = false;
    bool doZero = true;
    for (int i=poly.degree(); i >= 0; --i) {
        if (!poly.coeffs[i].isZero()) {
            if (doPrefix) out << " + ";
            out << '(' << poly.coeffs[i] << ')';
            doZero = false;
            if (i >= 1) {
                out << 'x';
                if (i > 1) {
                    out << '^' << i;
                }
            }
            doPrefix = true;
        }
    }
    if(doZero) {
        out << 0;
    }
    return out;
}


// Read until newline consisting of one polynomial in specified format
std::istream& operator>>(std::istream& in, Polynomial &poly){
    bool done = false;
    Rational coeff;
    int exp;
    if (in.eof() || in.peek() == '\n') return in;
    in >> coeff;
    if (in.eof() || in.peek() == '\n') return in;
    in >> exp;
    Polynomial ret{coeff, exp};
    while(!done) {
        if (in.eof() || in.peek() == '\n') {
            done = true;
        } else {
            in >> coeff;
            if (in.eof() || in.peek() == '\n') {
                done = true;
            } else {
                in >> exp;
                if (!coeff.isZero()) {
                    ret = ret + Polynomial{coeff, exp};
                }
            }
        }
    }
    poly = Polynomial(ret);
    return in;
}
