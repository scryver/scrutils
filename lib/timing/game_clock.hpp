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

    /**
     * @brief number of frames since last elapsed
     *
     * getFrames() => get frames since last frame reset
     * getFrames(-0.1f) => get frames since last frame reset (for all < 0.0f)
     * getFrames(0.0f) => get frames since last reset and reset
     * getFrames(0.2f) => returns -1 if the time since last reset is less than 0.2f
     *                    otherwise the number of frames and subtracts 0.2f from the
     *                    frame timer. timeElapsed is in seconds
     */
    int32_t getFrames(float timeElapsed = -1.0f);

    static GameClock& getInstance();

    GameClock(const GameClock&) = delete;
    GameClock& operator=(const GameClock&) = delete;
private:
    Clock m_clock;

    float m_frameTime;
    int32_t m_frames;

    GameClock() { }
    ~GameClock() { destroy(); }
};

}  // namespace Timing

}  // namespace Scryver

#define gameClock   Scryver::Timing::GameClock::getInstance()

#endif  // SCRYVER_TIMING_GAME_CLOCK_HPP
