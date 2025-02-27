#include "random_process.h"
#include <iostream>
#include "elma.h"
#include <random>

using namespace elma;
namespace random_process
{
    void Random_Process::update() {
        if (channel("link").size() < channel("link").capacity()) {
            std::random_device device; // Non-deterministic seed
            std::mt19937 gen(device());  // Mersenne Twister engine seeded with device
            std::uniform_real_distribution<double> myDist(0, std::nextafter(1, 1+1));
            channel("link").send(myDist(gen));
        }
        // else it's too full
    }
} 
