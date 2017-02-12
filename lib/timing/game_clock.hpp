#ifndef SCRYVER_TIMING_GAME_CLOCK_HPP
#define SCRYVER_TIMING_GAME_CLOCK_HPP

#include "Scryver/Timing/Clock.hpp"

namespace Scryver {

namespace Timing {

class GameClock
{
public:
    bool initialize();
    void destroy();

    float newFrame();
    float dt() const { return m_clock.lastTickTime(); }

    static GameClock& getInstance();

    GameClock(const GameClock&) = delete;
    GameClock& operator=(const GameClock&) = delete;
private:
    Clock m_clock;

    GameClock() { }
    ~GameClock() { destroy(); }
};

}  // namespace Timing

}  // namespace Scryver

#define gameClock   Scryver::Timing::GameClock::getInstance()

#endif  // SCRYVER_TIMING_GAME_CLOCK_HPP
