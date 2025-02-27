#include "Stopwatch.h"
#include <chrono>
#include <ratio>
#include <thread>

Stopwatch::Stopwatch() : running(false), begin(std::chrono::steady_clock::now()), end(std::chrono::steady_clock::now()), accumulatedTime(std::chrono::duration<double>::zero()) {};

Stopwatch::~Stopwatch() {}

void Stopwatch::start() {
    this->begin = std::chrono::steady_clock::now();
    this->running = true;
}

void Stopwatch::stop() {
    this->end =  std::chrono::steady_clock::now();
    this->running = false;
    this->accumulatedTime += this->end - this->begin;
}

void Stopwatch::reset() {
    this->begin = std::chrono::steady_clock::now();
    this->accumulatedTime = std::chrono::duration<double>::zero();
}

double Stopwatch::get_milliseconds() const {
    // Returns the current time difference in milliseconds or the saved difference if the stopwatch isn't running.
    return this->running ? std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - this->begin + this->accumulatedTime).count() :  std::chrono::duration<double, std::milli>(this->accumulatedTime).count();
}

double Stopwatch::get_nanoseconds() const {
    return this->running ? std::chrono::duration<double, std::nano>(std::chrono::steady_clock::now() - this->begin + this->accumulatedTime).count() :  std::chrono::duration<double, std::nano>(this->accumulatedTime).count();
}

double Stopwatch::get_seconds() const {
    return this->running ? std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(std::chrono::steady_clock::now() - this->begin + this->accumulatedTime).count() : std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(this->accumulatedTime).count();
}

double Stopwatch::get_minutes() const {
    return this->running ? std::chrono::duration_cast<std::chrono::duration<double, std::ratio<60>>>(std::chrono::steady_clock::now() - this->begin + this->accumulatedTime).count() : std::chrono::duration_cast<std::chrono::duration<double, std::ratio<60>>>(this->accumulatedTime).count();
}
