#ifndef TEST2_PROCESS_H
#define TEST2_PROCESS_H

#include <iostream>
#include "../include/elma.h"

using namespace elma;
namespace test2_process {
    class Test2_Process : public elma::Process {
        public:
            void update();
            void start() {}
            void stop() {}
            void init() {}
    };
}
#endif