#pragma once

#include <iostream>

#define EPS 0.000001

double abs(double x) {
    if (x < 0)
        return -x;
    return x;
}

bool is_zero(double x) { 
    if (abs(x) < EPS) return true;
    return false;
}

// complex numbers
class Complex {
public:
    Complex(double Re=0, double Im=0) : Re(Re), Im(Im) {}

    Complex operator+(const Complex& other) const {
        return Complex(Re + other.Re, Im + other.Im);
    }

    Complex operator-(const Complex& other) const {
        return Complex(Re - other.Re, Im - other.Im);
    }

    Complex operator*(const Complex& other) const {
        return Complex(Re * other.Re - Im * other.Im, Im * other.Re + Re * other.Im);
    }

    Complex& operator+=(const Complex& other) {
        Re += other.Re;
        Im += other.Im;
        return *this;
    }

    Complex operator/(int x) const {
        return Complex(Re / x, Im / x);
    }

    Complex sopr() const {
        return Complex(Re, -Im);
    }

    double GetRe() const { return Re; }
    double GetIm() const { return Im; }

private:
    double Re;
    double Im;
};

std::ostream& operator << (std::ostream &os, const Complex &complex) {
    double Re = complex.GetRe();
    if (is_zero(Re))
        Re = 0;
    double Im = complex.GetIm();
    if (is_zero(Im)) {
        return os << Re;
    } else if (is_zero(Re)) {
        return os << Im << "j";
    } else {
        return os << Re << "+" << Im << "j";
    }
}