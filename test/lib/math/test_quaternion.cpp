#include <gtest/gtest.h>

#include "Scryver/Math/Vector3D.hpp"

using Scryver::Math::Quaternionf;


TEST(Quaternion, Constructor)
{
    Quaternionf q;

    EXPECT_FLOAT_EQ(0.0f, q.s);
    EXPECT_FLOAT_EQ(0.0f, q.i);
    EXPECT_FLOAT_EQ(0.0f, q.j);
    EXPECT_FLOAT_EQ(0.0f, q.k);

    Quaternionf q2(1, -1, 2, -3);

    EXPECT_FLOAT_EQ(1.0f, q2.s);
    EXPECT_FLOAT_EQ(-1.0f, q2.i);
    EXPECT_FLOAT_EQ(2.0f, q2.j);
    EXPECT_FLOAT_EQ(-3.0f, q2.k);
}

TEST(Quaternion, Conjugate)
{
    Quaternionf q(1, -1, 2, -3);

    EXPECT_FLOAT_EQ(1.0f, q.s);
    EXPECT_FLOAT_EQ(-1.0f, q.i);
    EXPECT_FLOAT_EQ(2.0f, q.j);
    EXPECT_FLOAT_EQ(-3.0f, q.k);

    Quaternionf q2 = q.conjugate();

    EXPECT_FLOAT_EQ(1.0f, q2.s);
    EXPECT_FLOAT_EQ(1.0f, q2.i);
    EXPECT_FLOAT_EQ(-2.0f, q2.j);
    EXPECT_FLOAT_EQ(3.0f, q2.k);
}
