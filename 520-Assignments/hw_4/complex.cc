#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(re*re + im*im);

}

Complex operator+(const Complex& a, const Complex& b) {
    return Complex(a.real() + b.real(), a.imaginary() + b.imaginary());
}

Complex operator*(const Complex& a, const Complex& b) {
    return Complex(((a.real()* b.real()) + (a.imaginary() * b.imaginary() * -1)), ((a.imaginary() * b.real()) + (a.real() * b.imaginary())));
}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

bool operator==(const Complex& a, const Complex& b) {
    return (b.real() == a.real()) && (b.imaginary() == a.imaginary());
}

double Complex::real() const {
    return this->re;
}

double Complex::imaginary() const {
    return this->im;
}

Complex& Complex::conjugate() {
    im *= -1;
    return *this;
}