#include "test2_process.h"
#include <iostream>
#include "../include/elma.h"

using namespace elma;
namespace test2_process
{
    void test2_process::Test2_Process::update() {
        channel("link").send(2);
    }
} 
