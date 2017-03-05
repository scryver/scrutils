#include <gtest/gtest.h>

#include "Scryver/Inputs/UserInput.hpp"

using Scryver::Inputs::UserInput;
using Scryver::Math::Vector2Df;

TEST(UserInput, Constructor)
{
    UserInput uinp;

    EXPECT_FLOAT_EQ(0.0f, uinp.getMouseX());
}

TEST(UserInput, Initialize)
{
    UserInput uinp;

    EXPECT_TRUE(uinp.initialize());
}

TEST(UserInput, PressKey)
{
    UserInput uinp;

    uinp.initialize();

    uinp.pressKey(123);
    EXPECT_TRUE(uinp.isKeyPressed(123));
}

TEST(UserInput, ReleaseKey)
{
    UserInput uinp;

    uinp.initialize();

    uinp.releaseKey(123);
    EXPECT_FALSE(uinp.isKeyPressed(123));
    EXPECT_FALSE(uinp.isKeyReleased(123)); // Never been pressed
    uinp.pressKey(123);
    EXPECT_TRUE(uinp.isKeyPressed(123));
    EXPECT_FALSE(uinp.isKeyReleased(123));
    uinp.releaseKey(123);
    EXPECT_FALSE(uinp.isKeyPressed(123));
    EXPECT_FALSE(uinp.isKeyReleased(123)); // No update in between
    uinp.pressKey(123);
    EXPECT_TRUE(uinp.isKeyPressed(123));
    EXPECT_FALSE(uinp.isKeyReleased(123));
    uinp.update();
    uinp.releaseKey(123);
    EXPECT_FALSE(uinp.isKeyPressed(123));
    EXPECT_TRUE(uinp.isKeyReleased(123)); // After an update we can detect it
}

TEST(UserInput, SetMouseCoords)
{
    UserInput uinp;

    uinp.setMouseCoords(10.0f, 3.0f);

    EXPECT_FLOAT_EQ(10.0f, uinp.getMouseX());
    EXPECT_FLOAT_EQ(3.0f, uinp.getMouseY());

    uinp.setMouseCoords(Vector2Df(3.0f, 5.0f));

    EXPECT_FLOAT_EQ(3.0f, uinp.getMouseCoords().x);
    EXPECT_FLOAT_EQ(5.0f, uinp.getMouseCoords().y);
}

TEST(UserInput, KeyDown)
{
    UserInput uinp;

    uinp.initialize();

    EXPECT_FALSE(uinp.isKeyDown(123));
    uinp.pressKey(123);
    EXPECT_TRUE(uinp.isKeyDown(123));
    uinp.releaseKey(123);
    EXPECT_FALSE(uinp.isKeyDown(123));
}

TEST(UserInput, KeyUp)
{
    UserInput uinp;

    uinp.initialize();

    EXPECT_TRUE(uinp.isKeyUp(123));
    uinp.pressKey(123);
    EXPECT_FALSE(uinp.isKeyUp(123));
    uinp.releaseKey(123);
    EXPECT_TRUE(uinp.isKeyUp(123));
}

TEST(UserInput, UpdateResetsKeyPressed)
{
    UserInput uinp;

    uinp.initialize();

    uinp.pressKey(123);
    EXPECT_TRUE(uinp.isKeyPressed(123));
    EXPECT_TRUE(uinp.isKeyDown(123));
    EXPECT_FALSE(uinp.isKeyReleased(123));

    uinp.update();
    EXPECT_FALSE(uinp.isKeyPressed(123));
    EXPECT_TRUE(uinp.isKeyDown(123));
    EXPECT_FALSE(uinp.isKeyReleased(123));

    uinp.releaseKey(123);
    EXPECT_FALSE(uinp.isKeyPressed(123));
    EXPECT_FALSE(uinp.isKeyDown(123));
    EXPECT_TRUE(uinp.isKeyUp(123));
    EXPECT_TRUE(uinp.isKeyReleased(123));

    uinp.update();
    EXPECT_FALSE(uinp.isKeyPressed(123));
    EXPECT_FALSE(uinp.isKeyDown(123));
    EXPECT_TRUE(uinp.isKeyUp(123));
    EXPECT_FALSE(uinp.isKeyReleased(123));
}

TEST(UserInput, Destroy)
{
    UserInput uinp;

    uinp.pressKey(1);
    uinp.pressKey(5);
    uinp.update();
    uinp.releaseKey(1);
    uinp.destroy();

    EXPECT_FALSE(uinp.isKeyDown(1));
    EXPECT_FALSE(uinp.isKeyDown(5));
}
