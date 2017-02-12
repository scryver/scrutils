#include <gtest/gtest.h>

#include "Scryver/Math/Vector2D.hpp"
#include "Scryver/Math/Vector3D.hpp"

using Scryver::Math::Vector2D;
using Scryver::Math::Vector3D;

TEST(Vector2D, IfWeAreHereWeAreFine)
{
    Vector2D<float> vec(1, 2);
    EXPECT_FLOAT_EQ(1.0f, vec.x);
    EXPECT_FLOAT_EQ(2.0f, vec.y);
}

TEST(Vector3D, IfWeAreHereWeAreFine)
{
    Vector3D<float> vec(1, 2, 3);
    EXPECT_FLOAT_EQ(1.0f, vec.x);
    EXPECT_FLOAT_EQ(2.0f, vec.y);
    EXPECT_FLOAT_EQ(3.0f, vec.z);
}
