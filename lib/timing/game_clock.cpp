#include "game_clock.hpp"

using Scryver::Timing::GameClock;

bool GameClock::initialize()
{
    return m_clock.initialize();
}

void GameClock::destroy()
{
    m_clock.destroy();
}

float GameClock::newFrame()
{
    return m_clock.tick();
}

GameClock& GameClock::getInstance()
{
    static GameClock clock;

    return clock;
}
