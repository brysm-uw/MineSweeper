#ifndef RANDOM_PROCESS_H
#define RANDOM_PROCESS_H

#include <iostream>
#include "../include/elma.h"

using namespace elma;
namespace random_process {
    class Random_Process : public elma::Process {
        public:
            void update();
            void start() {}
            void stop() {}
            void init() {}
    };
}
#endif
