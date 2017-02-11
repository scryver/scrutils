#include <gtest/gtest.h>

#include <ctime>
#include <random>
#include <iostream>

#include "scryver/math/vector2d.hpp"

std::mt19937 vec2DrandEngine(time(NULL));

#if defined(FULL_TESTS) && FULL_TESTS
std::uniform_int_distribution<int> vec2DnrTestGen(100, 1000);
#else  // Fast testing
std::uniform_int_distribution<int> vec2DnrTestGen(1, 10);
#endif

std::uniform_real_distribution<float> vec2DfloatGen(-1.0f, 1.0f);

using std::cout;
using std::endl;
using std::flush;

using Scryver::Math::Vector2D;

TEST(Vector2D, Constructor)
{
    Vector2D<float> vec(1, 2);
    EXPECT_FLOAT_EQ(1.0f, vec.x);
    EXPECT_FLOAT_EQ(2.0f, vec.y);

    Vector2D<float> vec2;
    EXPECT_FLOAT_EQ(0.0f, vec2.x);
    EXPECT_FLOAT_EQ(0.0f, vec2.y);

    Vector2D<int> vecInt(15);
    EXPECT_EQ(15, vecInt.x);
    EXPECT_EQ(15, vecInt.y);

    Vector2D<int> vecInt2(1, -3);
    EXPECT_EQ(1, vecInt2.x);
    EXPECT_EQ(-3, vecInt2.y);

    Vector2D<unsigned char> vecUChar(1, -1);
    EXPECT_EQ(0x01, vecUChar.x);
    EXPECT_EQ(0xFF, vecUChar.y);
}

TEST(Vector2D, DefaultTemplates)
{
    Vector2Dd vec(1, 2);
    EXPECT_DOUBLE_EQ(1.0, vec.x);
    EXPECT_DOUBLE_EQ(2.0, vec.y);

    Vector2Df vec2;
    EXPECT_FLOAT_EQ(0.0f, vec2.x);
    EXPECT_FLOAT_EQ(0.0f, vec2.y);

    Vector2Di vecInt(1, -3);
    EXPECT_EQ(1, vecInt.x);
    EXPECT_EQ(-3, vecInt.y);

    Vector2Du vecUInt(1, -1);
    EXPECT_EQ(0x01, vecUInt.x);
    EXPECT_EQ(0xFFFFFFFF, vecUInt.y);
}

// TEST(Vector2D, AssignmentAddition)
// {
//     const int NR_TESTS = vec2DnrTestGen(vec2DrandEngine);

//     cout << "Running " << NR_TESTS << " vector assignment addition tests: " << flush;
//     for (int i = 0; i < NR_TESTS; i++)
//     {
//         cout << "." << flush;
//         Vector2D first(vec2DfloatGen(vec2DrandEngine),
//                        vec2DfloatGen(vec2DrandEngine));
//         Vector2D second(vec2DfloatGen(vec2DrandEngine),
//                         vec2DfloatGen(vec2DrandEngine));
//         Vector2D result = first;
//         result += second;

//         EXPECT_FLOAT_EQ(result.x, first.x + second.x);
//         EXPECT_FLOAT_EQ(result.y, first.y + second.y);
//     }
//     cout << endl;
// }

// TEST(Vector2D, AssignmentSubtraction)
// {
//     const int NR_TESTS = vec2DnrTestGen(vec2DrandEngine);

//     cout << "Running " << NR_TESTS << " vector assignment subtraction tests: " << flush;
//     for (int i = 0; i < NR_TESTS; i++)
//     {
//         cout << "." << flush;
//         Vector2D first(vec2DfloatGen(vec2DrandEngine),
//                        vec2DfloatGen(vec2DrandEngine));
//         Vector2D second(vec2DfloatGen(vec2DrandEngine),
//                         vec2DfloatGen(vec2DrandEngine));
//         Vector2D result = first;
//         result -= second;

//         EXPECT_FLOAT_EQ(result.x, first.x - second.x);
//         EXPECT_FLOAT_EQ(result.y, first.y - second.y);
//     }
//     cout << endl;
// }

// TEST(Vector2D, VectorAddition)
// {
//     Vector2D first(1, 2);
//     Vector2D second(3, 4);

//     Vector2D result1 = first + second;
//     Vector2D result2 = second + first;

//     EXPECT_FLOAT_EQ(result1.x, 4);
//     EXPECT_FLOAT_EQ(result1.y, 6);

//     EXPECT_FLOAT_EQ(result1.x, result2.x);
//     EXPECT_FLOAT_EQ(result1.y, result2.y);
// }

// TEST(Vector2D, VectorSubtraction)
// {
//     Vector2D first(1, 2);
//     Vector2D second(3, 4);

//     Vector2D result1 = first - second;
//     Vector2D result2 = second - first;

//     EXPECT_FLOAT_EQ(result1.x, -2);
//     EXPECT_FLOAT_EQ(result1.y, -2);

//     EXPECT_FLOAT_EQ(result2.x, 2);
//     EXPECT_FLOAT_EQ(result2.y, 2);

//     EXPECT_FLOAT_EQ(result1.x, -result2.x);
//     EXPECT_FLOAT_EQ(result1.y, -result2.y);
// }

// TEST(Vector2D, ScalarMultiplication)
// {
//     Vector2D vector(1, 2);
//     float scalar = 2.0f;

//     Vector2D result1 = scalar * vector;
//     Vector2D result2 = vector * scalar;

//     EXPECT_FLOAT_EQ(result1.x, 2);
//     EXPECT_FLOAT_EQ(result1.y, 4);

//     EXPECT_FLOAT_EQ(result1.x, result2.x);
//     EXPECT_FLOAT_EQ(result1.y, result2.y);

//     Vector2D vector2(-12, 3.5);

//     Vector2D result3 = 9 * vector2;
//     Vector2D result4 = vector2 * 9;

//     EXPECT_FLOAT_EQ(result3.x, -108);
//     EXPECT_FLOAT_EQ(result3.y, 31.5f);

//     EXPECT_FLOAT_EQ(result3.x, result4.x);
//     EXPECT_FLOAT_EQ(result3.y, result4.y);
// }
