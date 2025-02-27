#ifndef FILTER_H
#define FILTER_H

#include <iostream>
#include "../include/elma.h"
#include <json/json.h>
#include <deque>

using nlohmann::json;
using namespace elma;
namespace filter {
    class Filter : public elma::Process {
        public:
            void update();
            double value();
            void init();
            void start() {}
            void stop();
        private:
            double running_average = 0;
            int maxValues = 10;
            std::deque<double> values;
    };
}
#endif
