#include "clock.hpp"

#include <chrono>

using Scryver::Timing::Clock;

Clock::Clock()
    : m_runningTime(0.0)
    , m_lastTickTime(0.0f)
{
    // Empty
}

Clock::~Clock()
{
    destroy();
}

bool Clock::initialize()
{
    m_initTime = std::chrono::high_resolution_clock::now();
    m_tickTime = m_initTime;
    // m_stopTime = m_initTime;
    m_runningTime = 0.0;
    m_lastTickTime = 0.0f;

    return true;
}

void Clock::destroy()
{
    // Empty
}

void Clock::start()
{
    m_tickTime = std::chrono::high_resolution_clock::now();
}

void Clock::stop()
{
    auto newTime = std::chrono::high_resolution_clock::now();
    m_runningTime = std::chrono::duration_cast<std::chrono::duration<double>>(newTime - m_initTime).count();
    m_lastTickTime = std::chrono::duration_cast<std::chrono::duration<float>>(newTime - m_tickTime).count();
    m_tickTime = newTime;
}

float Clock::tick()
{
    stop();
    start();
    return lastTickTime();
}

void Clock::reset()
{
    initialize();
}
