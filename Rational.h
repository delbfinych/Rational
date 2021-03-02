#pragma once
#include <fstream>

/**
 * Дробь, x/y
 */
class Rational {
private:

    bool isNaN;
    int _numerator;
    int _denominator;

    Rational sum(const Rational&) const;
    Rational sub(const Rational&) const;
    Rational mul(const Rational&) const;
    Rational div(const Rational&) const;

    bool eq(const Rational&) const;
    bool lt(const Rational&) const;

    void print(std::ostream& out) const;
public:
    Rational();
    Rational(int, int);
    Rational(int);

    Rational operator+(const Rational& n);
    Rational operator*(const Rational& n);
    Rational operator/(const Rational& n);
    Rational operator-(const Rational& n);
    bool operator==(const Rational& n);
    bool operator<(const Rational& n);
    bool operator<=(const Rational& n);
    bool operator>(const Rational& n);
    bool operator>=(const Rational& n);
    bool operator!=(const Rational& n);
    friend std::ostream& operator<<(std::ostream& out, Rational& n);
    friend std::istream& operator>>(std::istream& in, Rational& n);
    // Сокращение
    Rational reduce();

    // *-1
    Rational neg() const;
    // ^-1
    Rational inv() const;
    bool isNan() const;
};
