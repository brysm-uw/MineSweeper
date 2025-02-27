#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <iostream>
#include "../include/elma.h"
#include <json/json.h>

using nlohmann::json;
using namespace elma;
namespace integrator {
    class integrator : public elma::Process {
        private:
            double _value = 0;
            bool firstRun = true;
        public:
            void update();
            double value();
            void init() {}
            void start() {}
            void stop() {}
    };
} 

#endif