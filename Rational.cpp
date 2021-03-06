#include <iostream>
#include "Rational.h"

namespace {
    unsigned int gcd(unsigned int a, unsigned int b) {
        return b != 0 ? gcd(b, a % b) : a;
    }

    int sign(int a) {
        return a > 0 ? 1 : -1;
    }

    bool isAnyNan(const Rational& n1, const Rational& n2) {
        return n1.isNan() || n2.isNan();
    }
}

Rational::Rational() {
    isNaN = false;
    _numerator = 1;
    _denominator = 1;
}

Rational::Rational(int x, int y) {
    isNaN = y == 0;
    _numerator = x;
    _denominator = std::abs(y);
    this->reduce();
}

Rational::Rational(int x) {
    isNaN = false;
    _numerator = x;
    _denominator = 1;
}


Rational Rational::reduce() {
    auto d = (gcd(std::abs(_numerator), _denominator));
    if (d > 0) {
        _numerator /= d;
        _denominator /= d;
    }
    return *this;
}

Rational Rational::inv() const {
    return {static_cast<int>(sign(_numerator) * _denominator),
            static_cast<int>(std::abs(_numerator))};
}

bool Rational::eq(const Rational& n) const {
    if (isAnyNan(*this, n)) {
        return false;
    }
    return this->_numerator == n._numerator
           && this->_denominator == n._denominator;
}


Rational Rational::neg() const {
    return {-_numerator, _denominator};
}

Rational Rational::mul(const Rational& n) const {
    return {_numerator * n._numerator,
                    _denominator * n._denominator};
}

Rational Rational::div(const Rational& n) const {
    return this->mul(n.inv()).reduce();
}

Rational Rational::sum(const Rational& n) const {
    auto commonDenominator = n._denominator * _denominator;

    return Rational(_numerator * n._denominator
                     + n._numerator * _denominator,
                    commonDenominator).reduce();
}

Rational Rational::sub(const Rational& n) const {
    return this->sum(n.neg());
}


bool Rational::lt(const Rational& n) const {
    return !isAnyNan(*this, n)
           && this->sub(n)._numerator < 0;
}

Rational Rational::operator+(const Rational& second) {
    return this->sum(second);
}

Rational Rational::operator*(const Rational& n) {
    return this->mul(n);
}

Rational Rational::operator/(const Rational& n) {
    return this->div(n);
}

Rational Rational::operator-(const Rational& n) {
    return this->sub(n);
}

bool Rational::operator==(const Rational& n) {
    return this->eq(n);
}

bool Rational::operator<(const Rational& n) {
    return this->lt(n);
}

bool Rational::operator<=(const Rational& n) {
    return !isAnyNan(*this, n)
           && !(*this > n);
}

bool Rational::operator>(const Rational& n) {
    return !isAnyNan(*this, n)
           && !((*this < n) || (*this == n));
}

bool Rational::operator>=(const Rational& n) {
    return !isAnyNan(*this, n)
           && !(*this < n);
}

bool Rational::operator!=(const Rational& n) {
    return !isAnyNan(*this, n)
           && !(*this == n);
}


bool Rational::isNan() const {
    return isNaN;
}

void Rational::print(std::ostream& out) const {
    if (isNan()) {
        out << "NaN";
    }
    else {
        out << _numerator << " % " << _denominator;
    }
}

std::ostream& operator<<(std::ostream& out, Rational& n) {
    n.print(out);
    return out;
}

std::istream& operator>>(std::istream& in, Rational& n) {
    in >> n._numerator;
    in.ignore(1, '%');
    in >> n._denominator;
    n._denominator = std::abs(n._denominator);
    n.isNaN = n._denominator == 0;
    n.reduce();
    return in;
}









