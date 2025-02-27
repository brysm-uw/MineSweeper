#include "gtest/gtest.h"
#include <iostream>
#include "Stopwatch.h"
#include <thread>
#include "elma.h"
#include "random_process.h"
#include "filter.h"
#include "test_process.h"
#include "integrator.h"
#include "test2_process.h"

#define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500));
namespace {
    TEST(Stopwatch, test1) {
        Stopwatch w;
        w.start();
        SLEEP;
        w.stop();
        // Testing each method here to see if conversions work as expected.
        ASSERT_NEAR(w.get_seconds(), 1.5, 0.1);
        ASSERT_NEAR(w.get_milliseconds(), 1500, 1);
        ASSERT_NEAR(w.get_nanoseconds(), 1500000000, 80000);
        ASSERT_NEAR(w.get_minutes(), 0.025, 0.002 );
        SLEEP;
        ASSERT_NEAR(w.get_seconds(), 1.5, 0.1);
        w.start();
        SLEEP;
        w.stop();
        ASSERT_NEAR(w.get_seconds(), 3, 0.1);
        w.reset();
        ASSERT_NEAR(w.get_seconds(), 0, 0.1);
    }

    TEST(RandomProcess, test1) {
        elma::Manager m;
        test_process::Test_Process t;
        random_process::Random_Process r;
        filter::Filter f;
        elma::Channel link("link");

        m.schedule(t, 1_ms)
         .schedule(f, 1_ms)
         .add_channel(link)
         .init()
         .run(100_ms);
        
        ASSERT_NEAR(f.value(), 0.5, 0.1);
    }

    TEST(Integrator, test1) {
        elma::Manager m;
        integrator::integrator i;
        test2_process::Test2_Process t;
        elma::Channel link("link");

        m.schedule(t, 1_ms)
         .schedule(i, 1_ms)
         .add_channel(link)
         .init()
         .run(100_ms);

         ASSERT_NEAR(i.value(), 200, 2);
    }
}