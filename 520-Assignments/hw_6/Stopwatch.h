#ifndef STOPWATCH
#define STOPWATCH

#include <iostream>
#include <chrono>

class Stopwatch {
    public:
        Stopwatch();
        ~Stopwatch();

        void start();
        void stop();
        void reset();
        double get_minutes() const;
        double get_seconds() const;
        double get_milliseconds() const;
        double get_nanoseconds() const;

    private:
        std::chrono::steady_clock::time_point begin;
        std::chrono::steady_clock::time_point end;
        std::chrono::duration<double> accumulatedTime;
        bool running = false;
};

#endif
