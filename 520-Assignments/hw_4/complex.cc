#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(re*re + im*im);

}

Complex operator+(const Complex& a, const Complex& b) {
    return Complex(a.re + b.re, a.im + b.im);
}

Complex operator*(const Complex& a, const Complex& b) {
    return Complex(((a.re * b.re) + (a.im * b.im * -1)), ((a.im * b.re) + (a.re * b.im)));
}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

bool operator==(const Complex& a, const Complex& b) {
    return (b->re == a.re) && (b->im == a.im);
}

double real() const {
    return re;
}

double imaginary() const {
    return im;
}

Complex& conjugate() {
    im *= -1;
    return *this;
}