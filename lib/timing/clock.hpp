#ifndef SCRYVER_TIMING_CLOCK_HPP
#define SCRYVER_TIMING_CLOCK_HPP

#include <chrono>

namespace Scryver {

namespace Timing {

class Clock
{
public:
    Clock();
    ~Clock();

    bool initialize();
    void destroy();

    void start();
    void stop();
    float tick();
    void reset();

    inline float lastTickTime() const { return m_lastTickTime; }
    inline double runningTime() const { return m_runningTime; }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_initTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_tickTime;

    double m_runningTime;
    float  m_lastTickTime;
};

}  // namespace Timing

}  // namespace Scryver

#endif  // SCRYVER_TIMING_CLOCK_HPP
