#ifndef TEST_PROCESS_H
#define TEST_PROCESS_H

#include <iostream>
#include "../include/elma.h"

using namespace elma;
namespace test_process {
    class Test_Process : public elma::Process {
        public:
            void update();
            void start() {}
            void stop() {}
            void init() {}
    };
}
#endif
