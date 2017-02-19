#include <gtest/gtest.h>

#include "Scryver/Math/Matrix4.hpp"

using Scryver::Math::Matrix4f;


TEST(Matrix4, Multiplication)
{
    Matrix4f m1;
    m1.m[0][0] = 1.0f; m1.m[0][1] = 2.0f; m1.m[0][2] = 3.0f; m1.m[0][3] = 4.0f;
    m1.m[1][0] = 5.0f; m1.m[1][1] = 6.0f; m1.m[1][2] = 7.0f; m1.m[1][3] = 8.0f;
    m1.m[2][0] = 9.0f; m1.m[2][1] = 0.0f; m1.m[2][2] = 1.0f; m1.m[2][3] = 2.0f;
    m1.m[3][0] = 3.0f; m1.m[3][1] = 4.0f; m1.m[3][2] = 5.0f; m1.m[3][3] = 6.0f;
    Matrix4f m2;
    m2.m[0][0] = 0.0f; m2.m[0][1] = 9.0f; m2.m[0][2] = 8.0f; m2.m[0][3] = 7.0f;
    m2.m[1][0] = 6.0f; m2.m[1][1] = 5.0f; m2.m[1][2] = 4.0f; m2.m[1][3] = 3.0f;
    m2.m[2][0] = 2.0f; m2.m[2][1] = 1.0f; m2.m[2][2] = 0.0f; m2.m[2][3] = 9.0f;
    m2.m[3][0] = 8.0f; m2.m[3][1] = 7.0f; m2.m[3][2] = 6.0f; m2.m[3][3] = 5.0f;

    Matrix4f m3 = m1 * m2;
    Matrix4f m4 = m2 * m1;

    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            ASSERT_NE(m1.m[i][j], m2.m[i][j]);
            ASSERT_NE(m1.m[i][j], m3.m[i][j]);
            ASSERT_NE(m1.m[i][j], m4.m[i][j]);
            ASSERT_NE(m2.m[i][j], m3.m[i][j]);
            ASSERT_NE(m2.m[i][j], m4.m[i][j]);
            ASSERT_NE(m3.m[i][j], m4.m[i][j]);
        }
    }

    ASSERT_FLOAT_EQ(1.0f * 0.0f + 2.0f * 6.0f + 3.0f * 2.0f + 4.0f * 8.0f, m3.m[0][0]);
    ASSERT_FLOAT_EQ(0.0f * 1.0f + 9.0f * 5.0f + 8.0f * 9.0f + 7.0f * 3.0f, m4.m[0][0]);
}