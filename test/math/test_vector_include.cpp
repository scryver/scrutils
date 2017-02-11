#include <gtest/gtest.h>

#include "scryver/math/vector2d.hpp"

using Scryver::Math::Vector2D;

TEST(Vector2D, IfWeAreHereWeAreFine)
{
    Vector2D<float> vec(1, 2);
    EXPECT_FLOAT_EQ(1.0f, vec.x);
    EXPECT_FLOAT_EQ(2.0f, vec.y);
}
