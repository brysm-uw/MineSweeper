#include <iostream>
#include "elma.h"
#include <json/json.h>
#include <vector>
#include "filter.h"
#include <deque>

using nlohmann::json;
using namespace elma;
namespace filter {
    void Filter::update() {
        values.push_back(channel("link").latest().get<double>());
    }

    double Filter::value() {
        return this->running_average;
    }

    void Filter::init() {
        this->values.clear();
    }

    void Filter::stop() {
        int ctr = 0;
        while (ctr < this->values.size() && ctr < this->maxValues) {
            std::cout << "value " << ctr << " in the queue: " << this->values.back() << std::endl;
            this->running_average += this->values.back();
            this->values.pop_back();
            ctr++;
        }
        this->running_average /= ctr;
    }
}