#include "complex.h"
#include <math.h>

Complex add(Complex num1, Complex num2) {
    Complex answer = {.real = num1.real + num2.real, .im = num1.im + num2.im};
    return answer;
}
Complex negate(Complex num) {
    Complex answer = {.real = -num.real, .im = -num.im};
    return answer;
}
Complex multiply(Complex num1, Complex num2) {
    Complex answer = {.real = (num1.real * num2.real) - (num1.im * num2.im), .im = (num1.real * num2.im) + (num1.im * num2.real)};
    return answer;
}
double magnitude(Complex num) {
    return sqrt(pow(num.real, 2) + pow(num.im, 2));
}