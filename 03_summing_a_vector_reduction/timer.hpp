#include <chrono>

class Timer {
  public:
    void reset();
    double elapsed() const;

  private:
    using Clock = std::chrono::high_resolution_clock;
    using Second = std::chrono::duration<double, std::ratio<1> >;
    std::chrono::time_point<Clock> curr{ Clock::now() };
};