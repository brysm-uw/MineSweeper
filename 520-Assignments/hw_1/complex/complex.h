#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct {
    double real;
    double im;
} Complex;

Complex add(Complex num1, Complex num2);
Complex negate(Complex num);
Complex multiply(Complex num1, Complex num2);
double magnitude(Complex num);

#endif