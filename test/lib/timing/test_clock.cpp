#include <gtest/gtest.h>

#include <ctime>
#include <chrono>
#include <thread>
#include <random>
#include <iostream>

#include "Scryver/Timing/Clock.hpp"
#include "Scryver/Timing/GameClock.hpp"

std::mt19937 clockRandEngine(time(NULL));
#if defined(FULL_TESTS) && FULL_TESTS
std::uniform_int_distribution<int> clockNrTestGen(10, 200);
std::uniform_int_distribution<int> clockMilliSecGen(0, 10000);
#else
std::uniform_int_distribution<int> clockNrTestGen(1, 10);
std::uniform_int_distribution<int> clockMilliSecGen(0, 100);
#endif

using std::cout;
using std::endl;
using std::flush;
using Scryver::Timing::Clock;

static const float THRESHOLD = 0.001f;

TEST(Clock, Initialize)
{
    Clock clock;
    EXPECT_TRUE(clock.initialize());
    clock.destroy();
}

TEST(GameClock, IsStatic)
{
    EXPECT_TRUE(gameClock.initialize());

    float tick = gameClock.newFrame();
    EXPECT_NE(0.0f, tick);
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    tick = gameClock.newFrame();

    EXPECT_GT(0.025f + 0.001, tick);
    EXPECT_LT(0.025f - 0.001, tick);
}

TEST(Clock, Reset)
{
    Clock clock;
    EXPECT_TRUE(clock.initialize());

    clock.start();
    EXPECT_FLOAT_EQ(0.0f, clock.lastTickTime());
    std::this_thread::sleep_for(std::chrono::milliseconds(80));
    EXPECT_FLOAT_EQ(0.0f, clock.lastTickTime());
    float tickLength = clock.tick();
    EXPECT_GT(tickLength, 0.079f);
    EXPECT_LT(tickLength, 0.082f);
    clock.tick();
    clock.tick();
    EXPECT_TRUE(clock.lastTickTime() < 0.00001);
    clock.reset();
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
    EXPECT_TRUE(clock.lastTickTime() < 0.00001);

    clock.destroy();
}

TEST(Clock, FrameTimeMeasuring)
{
    Clock clock;
    EXPECT_TRUE(clock.initialize());

    double accumulate = 0.0;

    clock.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    accumulate += 0.1;

    clock.tick();
    float timedTime = clock.lastTickTime();
    EXPECT_GT(timedTime, 0.09f);
    EXPECT_LT(timedTime, 0.11f);

    clock.tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    accumulate += 0.25;
    clock.tick();
    timedTime = clock.lastTickTime();
    EXPECT_GT(timedTime, 0.249f);
    EXPECT_LT(timedTime, 0.251f);

#if defined(FULL_TESTS) && FULL_TESTS
    const int NR_TESTS = clockNrTestGen(clockRandEngine);

    cout << "Running " << NR_TESTS << " timing tests: " << flush;
    for (int i = 0; i < NR_TESTS; i++) {
        cout << "." << flush;
        int sleepTimeMillisecs = clockMilliSecGen(clockRandEngine);
        float sleepTimeSecs = sleepTimeMillisecs / 1000.0f;
        accumulate += sleepTimeSecs;

        clock.tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeMillisecs));
        clock.tick();

        timedTime = clock.lastTickTime();

        EXPECT_GT(timedTime, sleepTimeSecs - THRESHOLD);
        EXPECT_LT(timedTime, sleepTimeSecs + THRESHOLD);
    }
    cout << endl;
#endif

    EXPECT_GT(accumulate + THRESHOLD * 2, clock.runningTime());
    EXPECT_LT(accumulate - THRESHOLD * 2, clock.runningTime());

    clock.destroy();
}

TEST(GameClock, IsReallyStatic)
{
    EXPECT_GT(0.025f + THRESHOLD, gameClock.dt());
    EXPECT_LT(0.025f - THRESHOLD, gameClock.dt());

    float tick = gameClock.newFrame();
    EXPECT_GT(tick, 0.0f);

    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    tick = gameClock.newFrame();
    EXPECT_FLOAT_EQ(tick, gameClock.dt());
}

TEST(GameClock, FrameCounter)
{
    float tick = gameClock.newFrame();
    EXPECT_GT(tick, 0.0f);
    int32_t frames = gameClock.getFrames(-1);
    EXPECT_EQ(5, frames);
    tick = gameClock.newFrame();
    frames = gameClock.getFrames(0);
    EXPECT_EQ(6, frames);
    tick = gameClock.newFrame();
    frames = gameClock.getFrames(0);
    EXPECT_EQ(1, frames);
    tick = gameClock.newFrame();
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    tick = gameClock.newFrame();
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    tick = gameClock.newFrame();
    frames = gameClock.getFrames(0.1f);
    EXPECT_EQ(-1, frames);
    frames = gameClock.getFrames(0.05f);
    EXPECT_EQ(3, frames);
}
