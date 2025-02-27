#include "test_process.h"
#include <iostream>
#include "../include/elma.h"

using namespace elma;
namespace test_process
{
    void test_process::Test_Process::update() {
        static bool isEven = false;
        if (channel("link").size() < channel("link").capacity()) {
            if (isEven) {
                isEven = !isEven;
                channel("link").send(0.75);
                
            }
            else {
                isEven = !isEven;
                channel("link").send(0.25);
        }
        }
    }
} 