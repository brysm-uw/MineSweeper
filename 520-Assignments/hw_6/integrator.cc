#include <iostream>
#include "../include/elma.h"
#include <json/json.h>
#include "integrator.h"

void integrator::integrator::update() {
    if (channel("link").nonempty()) {
        double v = channel("link").latest().get<double>();
        this->_value += delta() * v;
        std::cout << "integral value: " << this->value() << std::endl;
    }
}

double integrator::integrator::value() {
    return this->_value;
}
