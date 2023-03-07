#include "timer.hpp"

void Timer::reset() {
    curr = Clock::now();
}

double Timer::elapsed() const {
    return std::chrono::duration_cast<Second>(Clock::now() - curr).count();
}