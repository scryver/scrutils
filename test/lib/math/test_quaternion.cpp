#include <gtest/gtest.h>

#include "Scryver/Math/Vector3D.hpp"

using Scryver::Math::Quaternionf;


TEST(Quaternion, Constructor)
{
    Quaternionf q;

    EXPECT_FLOAT_EQ(1.0f, q.s);
    EXPECT_FLOAT_EQ(0.0f, q.i);
    EXPECT_FLOAT_EQ(0.0f, q.j);
    EXPECT_FLOAT_EQ(0.0f, q.k);

    Quaternionf q2(90, {0, 1, 0});

    EXPECT_FLOAT_EQ(0.70710677f, q2.s);
    EXPECT_FLOAT_EQ(0.0f, q2.i);
    EXPECT_FLOAT_EQ(0.70710677f, q2.j);
    EXPECT_FLOAT_EQ(0.0f, q2.k);
}

TEST(Quaternion, Conjugate)
{
    Quaternionf q(90, {1, 1, 1});

    EXPECT_FLOAT_EQ(0.70710677f, q.s);
    EXPECT_FLOAT_EQ(0.408248290464f, q.i);
    EXPECT_FLOAT_EQ(0.408248290464f, q.j);
    EXPECT_FLOAT_EQ(0.408248290464f, q.k);

    Quaternionf q2 = q.conjugate();

    EXPECT_FLOAT_EQ(0.70710677f, q2.s);
    EXPECT_FLOAT_EQ(-0.408248290464f, q2.i);
    EXPECT_FLOAT_EQ(-0.408248290464f, q2.j);
    EXPECT_FLOAT_EQ(-0.408248290464f, q2.k);
}
