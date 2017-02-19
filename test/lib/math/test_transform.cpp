#include <gtest/gtest.h>

#include "Scryver/Math/Transform3D.hpp"

using Scryver::Math::Transform3Df;


TEST(Transform, Constructor)
{
    Transform3Df transform;
    ASSERT_FLOAT_EQ(1.0f, transform.get().m[0][0]);
}

TEST(Transform, Scaling)
{
    Transform3Df transform;
    transform.scale(0.2f, 0.5f, 1.3f);
    ASSERT_FLOAT_EQ(0.2f, transform.get().m[0][0]);
    ASSERT_FLOAT_EQ(0.5f, transform.get().m[1][1]);
    ASSERT_FLOAT_EQ(1.3f, transform.get().m[2][2]);
}

TEST(Transform, Position)
{
    Transform3Df transform;
    transform.scale(0.2f, 0.5f, 1.3f);
    transform.worldPos(0.2f, 0.5f, 1.3f);
    ASSERT_FLOAT_EQ(0.2f, transform.get().m[0][0]);
    ASSERT_FLOAT_EQ(0.2f, transform.get().m[0][3]);
    ASSERT_FLOAT_EQ(0.5f, transform.get().m[1][1]);
    ASSERT_FLOAT_EQ(0.5f, transform.get().m[1][3]);
    ASSERT_FLOAT_EQ(1.3f, transform.get().m[2][2]);
    ASSERT_FLOAT_EQ(1.3f, transform.get().m[2][3]);
}

TEST(Transform, Rotation)
{
    Transform3Df transform;
    transform.scale(0.2f, 0.5f, 1.3f);
    transform.worldPos(0.2f, 0.5f, 1.3f);
    transform.rotate(0.0f, 0.0f, 180.0f);
    ASSERT_FLOAT_EQ(-0.2f, transform.get().m[0][0]);
    ASSERT_FLOAT_EQ(0.2f, transform.get().m[0][3]);
    ASSERT_FLOAT_EQ(-0.5f, transform.get().m[1][1]);
    ASSERT_FLOAT_EQ(0.5f, transform.get().m[1][3]);
    ASSERT_FLOAT_EQ(1.3f, transform.get().m[2][2]);
    ASSERT_FLOAT_EQ(1.3f, transform.get().m[2][3]);
}
