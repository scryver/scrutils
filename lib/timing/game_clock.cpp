#include "game_clock.hpp"

using Scryver::Timing::GameClock;

bool GameClock::initialize()
{
    m_frameTime = 0.0f;
    m_frames = 0;
    return m_clock.initialize();
}

void GameClock::destroy()
{
    m_frameTime = 0.0f;
    m_frames = 0;
    m_clock.destroy();
}

float GameClock::newFrame()
{
    float t = m_clock.tick();
    m_frameTime += t;
    ++m_frames;
    return t;
}

int32_t GameClock::getFrames(float timeElapsed)
{
    int32_t frames;
    if (timeElapsed < 0.0f)
    {
        frames = m_frames;
    }
    else if (timeElapsed == 0.0f)
    {
        m_frameTime = 0.0f;
        frames = m_frames;
        m_frames = 0;
    }
    else if (m_frameTime >= timeElapsed)
    {
        m_frameTime -= timeElapsed;
        frames = m_frames;
        m_frames = 0;
    }
    else
    {
        frames = -1;
    }

    return frames;
}


GameClock& GameClock::getInstance()
{
    static GameClock clock;

    return clock;
}
