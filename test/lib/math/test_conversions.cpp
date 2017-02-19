#include <gtest/gtest.h>

#include "Scryver/Math/Constants.hpp"
#include "Scryver/Math/Conversions.hpp"


TEST(Conversion, ToRadian)
{
    float f_degree = 0.0f;
    EXPECT_FLOAT_EQ(0.0f, Scryver::Math::toRadian(f_degree));

    f_degree = 180.0f;
    EXPECT_FLOAT_EQ(Scryver::Math::fPI, Scryver::Math::toRadian(f_degree));

    f_degree = 90.0f;
    EXPECT_FLOAT_EQ(Scryver::Math::fPIdiv2, Scryver::Math::toRadian(f_degree));

    f_degree = 60.0f;
    EXPECT_FLOAT_EQ(Scryver::Math::fPIdiv3, Scryver::Math::toRadian(f_degree));

    f_degree = 45.0f;
    EXPECT_FLOAT_EQ(Scryver::Math::fPIdiv4, Scryver::Math::toRadian(f_degree));

    f_degree = 360.0f;
    EXPECT_FLOAT_EQ(Scryver::Math::f2PI, Scryver::Math::toRadian(f_degree));

    double d_degree = 0.0;
    EXPECT_DOUBLE_EQ(0.0, Scryver::Math::toRadian(d_degree));

    d_degree = 180.0;
    EXPECT_DOUBLE_EQ(Scryver::Math::dPI, Scryver::Math::toRadian(d_degree));

    d_degree = 90.0;
    EXPECT_DOUBLE_EQ(Scryver::Math::dPIdiv2, Scryver::Math::toRadian(d_degree));

    d_degree = 60.0;
    EXPECT_DOUBLE_EQ(Scryver::Math::dPIdiv3, Scryver::Math::toRadian(d_degree));

    d_degree = 45.0;
    EXPECT_DOUBLE_EQ(Scryver::Math::dPIdiv4, Scryver::Math::toRadian(d_degree));

    d_degree = 360.0;
    EXPECT_DOUBLE_EQ(Scryver::Math::d2PI, Scryver::Math::toRadian(d_degree));
}

TEST(Conversion, ToDegree)
{
    float f_radian = 0.0f;
    EXPECT_FLOAT_EQ(0.0f, Scryver::Math::toDegree(f_radian));

    f_radian = Scryver::Math::fPI;
    EXPECT_FLOAT_EQ(180.0f, Scryver::Math::toDegree(f_radian));

    f_radian = Scryver::Math::fPIdiv2;
    EXPECT_FLOAT_EQ(90.0f, Scryver::Math::toDegree(f_radian));

    f_radian = Scryver::Math::fPIdiv3;
    EXPECT_FLOAT_EQ(60.0f, Scryver::Math::toDegree(f_radian));

    f_radian = Scryver::Math::fPIdiv4;
    EXPECT_FLOAT_EQ(45.0f, Scryver::Math::toDegree(f_radian));

    f_radian = Scryver::Math::f2PI;
    EXPECT_FLOAT_EQ(360.0f, Scryver::Math::toDegree(f_radian));

    double d_radian = 0.0;
    EXPECT_DOUBLE_EQ(0.0, Scryver::Math::toDegree(d_radian));

    d_radian = Scryver::Math::dPI;
    EXPECT_DOUBLE_EQ(180.0, Scryver::Math::toDegree(d_radian));

    d_radian = Scryver::Math::dPIdiv2;
    EXPECT_DOUBLE_EQ(90.0, Scryver::Math::toDegree(d_radian));

    d_radian = Scryver::Math::dPIdiv3;
    EXPECT_DOUBLE_EQ(60.0, Scryver::Math::toDegree(d_radian));

    d_radian = Scryver::Math::dPIdiv4;
    EXPECT_DOUBLE_EQ(45.0, Scryver::Math::toDegree(d_radian));

    d_radian = Scryver::Math::d2PI;
    EXPECT_DOUBLE_EQ(360.0, Scryver::Math::toDegree(d_radian));
}
