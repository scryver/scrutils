#include <gtest/gtest.h>

#include <ctime>
#include <random>
#include <iostream>

#include "Scryver/Math/Vector2D.hpp"

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
using Scryver::Math::Vector2Df;

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
    EXPECT_EQ(0x01u, vecUChar.x);
    EXPECT_EQ(0xFFu, vecUChar.y);
}

TEST(Vector2D, DefaultTemplates)
{
    Scryver::Math::Vector2Dd vec(1, 2);
    EXPECT_DOUBLE_EQ(1.0, vec.x);
    EXPECT_DOUBLE_EQ(2.0, vec.y);

    Scryver::Math::Vector2Df vec2;
    EXPECT_FLOAT_EQ(0.0f, vec2.x);
    EXPECT_FLOAT_EQ(0.0f, vec2.y);

    Scryver::Math::Vector2Di vecInt(1, -3);
    EXPECT_EQ(1, vecInt.x);
    EXPECT_EQ(-3, vecInt.y);

    Scryver::Math::Vector2Du vecUInt(1, -1);
    EXPECT_EQ(0x01u, vecUInt.x);
    EXPECT_EQ(0xFFFFFFFFu, vecUInt.y);
}

TEST(Vector2D, CopyConstructor)
{
    Vector2Df vec(1, 2);
    EXPECT_FLOAT_EQ(1.0f, vec.x);
    EXPECT_FLOAT_EQ(2.0f, vec.y);

    Vector2Df vec2(vec);
    EXPECT_FLOAT_EQ(1.0f, vec2.x);
    EXPECT_FLOAT_EQ(2.0f, vec2.y);
}

TEST(Vector2D, AssingmentConstructor)
{
    Vector2Df vec(1, 2);
    EXPECT_FLOAT_EQ(1.0f, vec.x);
    EXPECT_FLOAT_EQ(2.0f, vec.y);

    Vector2Df vec2 = vec;
    EXPECT_FLOAT_EQ(1.0f, vec2.x);
    EXPECT_FLOAT_EQ(2.0f, vec2.y);

    Vector2Df vec3 = Vector2Df(2.0f, 1.0f);
    EXPECT_FLOAT_EQ(2.0f, vec3.x);
    EXPECT_FLOAT_EQ(1.0f, vec3.y);
}

TEST(Vector2D, AssignmentAddition)
{
    const int NR_TESTS = vec2DnrTestGen(vec2DrandEngine);

    cout << "Running " << NR_TESTS << " vector assignment addition tests: " << flush;
    for (int i = 0; i < NR_TESTS; i++)
    {
        cout << "." << flush;
        Vector2Df first(vec2DfloatGen(vec2DrandEngine),
                        vec2DfloatGen(vec2DrandEngine));
        Vector2Df second(vec2DfloatGen(vec2DrandEngine),
                         vec2DfloatGen(vec2DrandEngine));
        Vector2Df result = first;
        result += second;

        EXPECT_FLOAT_EQ(result.x, first.x + second.x);
        EXPECT_FLOAT_EQ(result.y, first.y + second.y);

        Vector2Df res2 = first;
        float addition = vec2DfloatGen(vec2DrandEngine);
        res2 += addition;
        EXPECT_FLOAT_EQ(res2.x, first.x + addition);
        EXPECT_FLOAT_EQ(res2.y, first.y + addition);
    }
    cout << endl;
}

TEST(Vector2D, AssignmentSubtraction)
{
    const int NR_TESTS = vec2DnrTestGen(vec2DrandEngine);

    cout << "Running " << NR_TESTS << " vector assignment subtraction tests: " << flush;
    for (int i = 0; i < NR_TESTS; i++)
    {
        cout << "." << flush;
        Vector2Df first(vec2DfloatGen(vec2DrandEngine),
                       vec2DfloatGen(vec2DrandEngine));
        Vector2Df second(vec2DfloatGen(vec2DrandEngine),
                        vec2DfloatGen(vec2DrandEngine));
        Vector2Df result = first;
        result -= second;

        EXPECT_FLOAT_EQ(result.x, first.x - second.x);
        EXPECT_FLOAT_EQ(result.y, first.y - second.y);

        Vector2Df res2 = first;
        float subtraction = vec2DfloatGen(vec2DrandEngine);
        res2 -= subtraction;
        EXPECT_FLOAT_EQ(res2.x, first.x - subtraction);
        EXPECT_FLOAT_EQ(res2.y, first.y - subtraction);
    }
    cout << endl;
}

TEST(Vector2D, VectorAddition)
{
    Vector2Df first(1, 2);
    Vector2Df second(3, 4);

    Vector2Df result1 = first + second;
    Vector2Df result2 = second + first;

    EXPECT_FLOAT_EQ(result1.x, 4);
    EXPECT_FLOAT_EQ(result1.y, 6);

    EXPECT_FLOAT_EQ(result1.x, result2.x);
    EXPECT_FLOAT_EQ(result1.y, result2.y);

    float addition = vec2DfloatGen(vec2DrandEngine);
    result1 = first + addition;
    result2 = addition + first;
    EXPECT_FLOAT_EQ(result1.x, first.x + addition);
    EXPECT_FLOAT_EQ(result1.y, first.y + addition);
    EXPECT_FLOAT_EQ(result1.x, result2.x);
    EXPECT_FLOAT_EQ(result1.y, result2.y);
}

TEST(Vector2D, VectorSubtraction)
{
    Vector2Df first(1, 2);
    Vector2Df second(3, 4);

    Vector2Df result1 = first - second;
    Vector2Df result2 = second - first;

    EXPECT_FLOAT_EQ(result1.x, -2);
    EXPECT_FLOAT_EQ(result1.y, -2);

    EXPECT_FLOAT_EQ(result2.x, 2);
    EXPECT_FLOAT_EQ(result2.y, 2);

    EXPECT_FLOAT_EQ(result1.x, -result2.x);
    EXPECT_FLOAT_EQ(result1.y, -result2.y);

    float subtraction = vec2DfloatGen(vec2DrandEngine);
    result1 = first - subtraction;
    result2 = subtraction - first;
    EXPECT_FLOAT_EQ(result1.x, first.x - subtraction);
    EXPECT_FLOAT_EQ(result1.y, first.y - subtraction);
    EXPECT_FLOAT_EQ(result2.x, subtraction - first.x);
    EXPECT_FLOAT_EQ(result2.y, subtraction - first.y);
}

TEST(Vector2D, ScalarMultiplication)
{
    Vector2Df vector(1, 2);
    float scalar = 2.0f;

    Vector2Df result1 = scalar * vector;
    Vector2Df result2 = vector * scalar;

    EXPECT_FLOAT_EQ(result1.x, 2);
    EXPECT_FLOAT_EQ(result1.y, 4);

    EXPECT_FLOAT_EQ(result1.x, result2.x);
    EXPECT_FLOAT_EQ(result1.y, result2.y);

    Vector2Df vector2(-12, 3.5);

    Vector2Df result3 = 9 * vector2;
    Vector2Df result4 = vector2 * 9;

    EXPECT_FLOAT_EQ(result3.x, -108);
    EXPECT_FLOAT_EQ(result3.y, 31.5f);

    EXPECT_FLOAT_EQ(result3.x, result4.x);
    EXPECT_FLOAT_EQ(result3.y, result4.y);
}
