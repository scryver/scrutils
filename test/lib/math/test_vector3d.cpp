#include <gtest/gtest.h>

#include <ctime>
#include <random>
#include <iostream>

#include "Scryver/Math/Vector3D.hpp"

std::mt19937 vec3DrandEngine(time(NULL));

#if defined(FULL_TESTS) && FULL_TESTS
std::uniform_int_distribution<int> vec3DnrTestGen(100, 1000);
#else  // Fast testing
std::uniform_int_distribution<int> vec3DnrTestGen(1, 10);
#endif

std::uniform_real_distribution<float> vec3DfloatGen(-1.0f, 1.0f);

using std::cout;
using std::endl;
using std::flush;

using Scryver::Math::Vector3D;
using Scryver::Math::Vector3Df;

TEST(Vector3D, Constructor)
{
    Vector3D<float> vec(1, 2, 3);
    EXPECT_FLOAT_EQ(1.0f, vec.x);
    EXPECT_FLOAT_EQ(2.0f, vec.y);
    EXPECT_FLOAT_EQ(3.0f, vec.z);

    Vector3D<float> vec2;
    EXPECT_FLOAT_EQ(0.0f, vec2.x);
    EXPECT_FLOAT_EQ(0.0f, vec2.y);
    EXPECT_FLOAT_EQ(0.0f, vec2.z);

    Vector3D<int> vecInt(15);
    EXPECT_EQ(15, vecInt.x);
    EXPECT_EQ(15, vecInt.y);
    EXPECT_EQ(15, vecInt.z);

    Vector3D<int> vecInt2(1, -3, 14);
    EXPECT_EQ(1, vecInt2.x);
    EXPECT_EQ(-3, vecInt2.y);
    EXPECT_EQ(14, vecInt2.z);

    Vector3D<unsigned char> vecUChar(1, -1, 0);
    EXPECT_EQ(0x01u, vecUChar.x);
    EXPECT_EQ(0xFFu, vecUChar.y);
    EXPECT_EQ(0u, vecUChar.z);
}

TEST(Vector3D, DefaultTemplates)
{
    Scryver::Math::Vector3Dd vec(1, 2, 3);
    EXPECT_DOUBLE_EQ(1.0, vec.x);
    EXPECT_DOUBLE_EQ(2.0, vec.y);
    EXPECT_DOUBLE_EQ(3.0, vec.z);

    Scryver::Math::Vector3Df vec2;
    EXPECT_FLOAT_EQ(0.0f, vec2.x);
    EXPECT_FLOAT_EQ(0.0f, vec2.y);
    EXPECT_FLOAT_EQ(0.0f, vec2.z);

    Scryver::Math::Vector3Di vecInt(1, -3, 4);
    EXPECT_EQ(1, vecInt.x);
    EXPECT_EQ(-3, vecInt.y);
    EXPECT_EQ(4, vecInt.z);

    Scryver::Math::Vector3Du vecUInt(1, -1, 4);
    EXPECT_EQ(0x01u, vecUInt.x);
    EXPECT_EQ(0xFFFFFFFFu, vecUInt.y);
    EXPECT_EQ(4u, vecUInt.z);
}

TEST(Vector3D, CopyConstructor)
{
    Vector3Df vec(1, 2, 3);
    EXPECT_FLOAT_EQ(1.0f, vec.x);
    EXPECT_FLOAT_EQ(2.0f, vec.y);
    EXPECT_FLOAT_EQ(3.0f, vec.z);

    Vector3Df vec2(vec);
    EXPECT_FLOAT_EQ(1.0f, vec2.x);
    EXPECT_FLOAT_EQ(2.0f, vec2.y);
    EXPECT_FLOAT_EQ(3.0f, vec2.z);
}

TEST(Vector3D, AssingmentConstructor)
{
    Vector3Df vec(1, 2, 3);
    EXPECT_FLOAT_EQ(1.0f, vec.x);
    EXPECT_FLOAT_EQ(2.0f, vec.y);
    EXPECT_FLOAT_EQ(3.0f, vec.z);

    Vector3Df vec2 = vec;
    EXPECT_FLOAT_EQ(1.0f, vec2.x);
    EXPECT_FLOAT_EQ(2.0f, vec2.y);
    EXPECT_FLOAT_EQ(3.0f, vec2.z);

    Vector3Df vec3 = Vector3Df(2.0f, 1.0f, 0.0f);
    EXPECT_FLOAT_EQ(2.0f, vec3.x);
    EXPECT_FLOAT_EQ(1.0f, vec3.y);
    EXPECT_FLOAT_EQ(0.0f, vec3.z);
}

TEST(Vector3D, UnaryMinus)
{
    Vector3Df v1(1, 2, 3);
    Vector3Df v2 = -v1;
    EXPECT_FLOAT_EQ(1.0f, v1.x);
    EXPECT_FLOAT_EQ(2.0f, v1.y);
    EXPECT_FLOAT_EQ(3.0f, v1.z);
    EXPECT_FLOAT_EQ(-1.0f, v2.x);
    EXPECT_FLOAT_EQ(-2.0f, v2.y);
    EXPECT_FLOAT_EQ(-3.0f, v2.z);
}

TEST(Vector3D, AssignmentAddition)
{
    const int NR_TESTS = vec3DnrTestGen(vec3DrandEngine);

    cout << "Running " << NR_TESTS << " vector assignment addition tests: " << flush;
    for (int i = 0; i < NR_TESTS; i++)
    {
        cout << "." << flush;
        Vector3Df first(vec3DfloatGen(vec3DrandEngine),
                        vec3DfloatGen(vec3DrandEngine),
                        vec3DfloatGen(vec3DrandEngine));
        Vector3Df second(vec3DfloatGen(vec3DrandEngine),
                         vec3DfloatGen(vec3DrandEngine),
                         vec3DfloatGen(vec3DrandEngine));
        Vector3Df result = first;
        result += second;

        EXPECT_FLOAT_EQ(result.x, first.x + second.x);
        EXPECT_FLOAT_EQ(result.y, first.y + second.y);
        EXPECT_FLOAT_EQ(result.z, first.z + second.z);

        Vector3Df res2 = first;
        float addition = vec3DfloatGen(vec3DrandEngine);
        res2 += addition;
        EXPECT_FLOAT_EQ(res2.x, first.x + addition);
        EXPECT_FLOAT_EQ(res2.y, first.y + addition);
        EXPECT_FLOAT_EQ(res2.z, first.z + addition);
    }
    cout << endl;
}

TEST(Vector3D, AssignmentSubtraction)
{
    const int NR_TESTS = vec3DnrTestGen(vec3DrandEngine);

    cout << "Running " << NR_TESTS << " vector assignment subtraction tests: " << flush;
    for (int i = 0; i < NR_TESTS; i++)
    {
        cout << "." << flush;
        Vector3Df first(vec3DfloatGen(vec3DrandEngine),
                        vec3DfloatGen(vec3DrandEngine),
                        vec3DfloatGen(vec3DrandEngine));
        Vector3Df second(vec3DfloatGen(vec3DrandEngine),
                         vec3DfloatGen(vec3DrandEngine),
                         vec3DfloatGen(vec3DrandEngine));
        Vector3Df result = first;
        result -= second;

        EXPECT_FLOAT_EQ(result.x, first.x - second.x);
        EXPECT_FLOAT_EQ(result.y, first.y - second.y);
        EXPECT_FLOAT_EQ(result.z, first.z - second.z);

        Vector3Df res2 = first;
        float subtraction = vec3DfloatGen(vec3DrandEngine);
        res2 -= subtraction;
        EXPECT_FLOAT_EQ(res2.x, first.x - subtraction);
        EXPECT_FLOAT_EQ(res2.y, first.y - subtraction);
        EXPECT_FLOAT_EQ(res2.z, first.z - subtraction);
    }
    cout << endl;
}

TEST(Vector3D, VectorAddition)
{
    Vector3Df first(1, 2, 3);
    Vector3Df second(4, 5, 6);

    Vector3Df result1 = first + second;
    Vector3Df result2 = second + first;

    EXPECT_FLOAT_EQ(result1.x, 5.0f);
    EXPECT_FLOAT_EQ(result1.y, 7.0f);
    EXPECT_FLOAT_EQ(result1.z, 9.0f);

    EXPECT_FLOAT_EQ(result1.x, result2.x);
    EXPECT_FLOAT_EQ(result1.y, result2.y);
    EXPECT_FLOAT_EQ(result1.z, result2.z);

    float addition = vec3DfloatGen(vec3DrandEngine);
    result1 = first + addition;
    result2 = addition + first;
    EXPECT_FLOAT_EQ(result1.x, first.x + addition);
    EXPECT_FLOAT_EQ(result1.y, first.y + addition);
    EXPECT_FLOAT_EQ(result1.z, first.z + addition);
    EXPECT_FLOAT_EQ(result1.x, result2.x);
    EXPECT_FLOAT_EQ(result1.y, result2.y);
    EXPECT_FLOAT_EQ(result1.z, result2.z);
}

TEST(Vector3D, VectorSubtraction)
{
    Vector3Df first(1, 2, 3);
    Vector3Df second(4, 5, 6);

    Vector3Df result1 = first - second;
    Vector3Df result2 = second - first;

    EXPECT_FLOAT_EQ(result1.x, -3);
    EXPECT_FLOAT_EQ(result1.y, -3);
    EXPECT_FLOAT_EQ(result1.z, -3);

    EXPECT_FLOAT_EQ(result2.x, 3);
    EXPECT_FLOAT_EQ(result2.y, 3);
    EXPECT_FLOAT_EQ(result2.z, 3);

    EXPECT_FLOAT_EQ(result1.x, -result2.x);
    EXPECT_FLOAT_EQ(result1.y, -result2.y);
    EXPECT_FLOAT_EQ(result1.z, -result2.z);

    float subtraction = vec3DfloatGen(vec3DrandEngine);
    result1 = first - subtraction;
    result2 = subtraction - first;
    EXPECT_FLOAT_EQ(result1.x, first.x - subtraction);
    EXPECT_FLOAT_EQ(result1.y, first.y - subtraction);
    EXPECT_FLOAT_EQ(result1.z, first.z - subtraction);
    EXPECT_FLOAT_EQ(result2.x, subtraction - first.x);
    EXPECT_FLOAT_EQ(result2.y, subtraction - first.y);
    EXPECT_FLOAT_EQ(result2.z, subtraction - first.z);
}

TEST(Vector3D, ScalarMultiplication)
{
    Vector3Df vector(1, 2, 3);
    float scalar = 2.0f;

    Vector3Df result1 = scalar * vector;
    Vector3Df result2 = vector * scalar;

    EXPECT_FLOAT_EQ(result1.x, 2);
    EXPECT_FLOAT_EQ(result1.y, 4);
    EXPECT_FLOAT_EQ(result1.z, 6);

    EXPECT_FLOAT_EQ(result1.x, result2.x);
    EXPECT_FLOAT_EQ(result1.y, result2.y);
    EXPECT_FLOAT_EQ(result1.z, result2.z);

    Vector3Df vector2(-12, 3.5, 1.5);

    Vector3Df result3 = 9 * vector2;
    Vector3Df result4 = vector2 * 9;

    EXPECT_FLOAT_EQ(result3.x, -108);
    EXPECT_FLOAT_EQ(result3.y, 31.5f);
    EXPECT_FLOAT_EQ(result3.z, 13.5f);

    EXPECT_FLOAT_EQ(result3.x, result4.x);
    EXPECT_FLOAT_EQ(result3.y, result4.y);
    EXPECT_FLOAT_EQ(result3.z, result4.z);
}

TEST(Vector3D, Length)
{
    Vector3Df v(2, 0, 0);
    EXPECT_FLOAT_EQ(2.0f, v.length());
    EXPECT_FLOAT_EQ(4.0f, v.lengthSquared());
    v.x = 1.0f;
    v.y = 2.0f;
    v.z = 3.0f;
    EXPECT_FLOAT_EQ(3.7416573867739413f, v.length());
    EXPECT_FLOAT_EQ(14.0f, v.lengthSquared());
}

TEST(Vector3D, Normalize)
{
    Vector3Df vector(1, 2, 3);

    Vector3Df vn = vector.normalized();

    Vector3Df vector2(3, 4, 5);
    vector2.normalize();

    Vector3Df vs = vn.normalized();

    EXPECT_FLOAT_EQ(1.0f, vn.length());
    EXPECT_FLOAT_EQ(1.0f, vs.length());
    EXPECT_FLOAT_EQ(1.0f, vs.lengthSquared());
    EXPECT_GT(vector.length(), 1.0f);
    EXPECT_FLOAT_EQ(1.0f, vector2.length());
}

TEST(Vector3D, CrossProduct)
{
    Vector3Df v1(1, 0, 0);
    Vector3Df v2(0, 1, 0);

    Vector3Df cross = v1.cross(v2);
    EXPECT_FLOAT_EQ(0.0f, cross.x);
    EXPECT_FLOAT_EQ(0.0f, cross.y);
    EXPECT_FLOAT_EQ(1.0f, cross.z);

    Vector3Df v3(1, 1, 1);
    Vector3Df v4(-1, 1, 0);

    cross = v3.cross(v4);
    EXPECT_FLOAT_EQ(-1.0f, cross.x);
    EXPECT_FLOAT_EQ(-1.0f, cross.y);
    EXPECT_FLOAT_EQ(2.0f, cross.z);

    cross = v1.cross(v3);
    EXPECT_FLOAT_EQ(0.0f, cross.x);
    EXPECT_FLOAT_EQ(-1.0f, cross.y);
    EXPECT_FLOAT_EQ(1.0f, cross.z);

    cross = v1.cross(v4);
    EXPECT_FLOAT_EQ(0.0f, cross.x);
    EXPECT_FLOAT_EQ(0.0f, cross.y);
    EXPECT_FLOAT_EQ(1.0f, cross.z);

    cross = v2.cross(v3);
    EXPECT_FLOAT_EQ(1.0f, cross.x);
    EXPECT_FLOAT_EQ(0.0f, cross.y);
    EXPECT_FLOAT_EQ(-1.0f, cross.z);

    cross = v3.cross(v1);
    EXPECT_FLOAT_EQ(0.0f, cross.x);
    EXPECT_FLOAT_EQ(1.0f, cross.y);
    EXPECT_FLOAT_EQ(-1.0f, cross.z);

    cross = v3.cross(v2);
    EXPECT_FLOAT_EQ(-1.0f, cross.x);
    EXPECT_FLOAT_EQ(0.0f, cross.y);
    EXPECT_FLOAT_EQ(1.0f, cross.z);

    cross = v4.cross(v3);
    EXPECT_FLOAT_EQ(1.0f, cross.x);
    EXPECT_FLOAT_EQ(1.0f, cross.y);
    EXPECT_FLOAT_EQ(-2.0f, cross.z);
}

TEST(Vector3D, RotateAroundAxis)
{
    Vector3Df v1(1, 0, 0);

    v1.rotate(90, Vector3Df(0, 1, 0));
    EXPECT_FLOAT_EQ(0.0f, v1.x);
    EXPECT_FLOAT_EQ(0.0f, v1.y);
    EXPECT_FLOAT_EQ(-1.0f, v1.z);

    v1.rotate(90, Vector3Df(0, 1, 0));
    EXPECT_FLOAT_EQ(-1.0f, v1.x);
    EXPECT_FLOAT_EQ(0.0f, v1.y);
    EXPECT_FLOAT_EQ(0.0f, v1.z);

    v1.rotate(90, Vector3Df(0, 1, 0));
    EXPECT_FLOAT_EQ(0.0f, v1.x);
    EXPECT_FLOAT_EQ(0.0f, v1.y);
    EXPECT_FLOAT_EQ(1.0f, v1.z);

    v1.rotate(90, Vector3Df(0, 1, 0));
    EXPECT_FLOAT_EQ(1.0f, v1.x);
    EXPECT_FLOAT_EQ(0.0f, v1.y);
    EXPECT_FLOAT_EQ(0.0f, v1.z);
}

TEST(Vector3D, RotatedAroundAxis)
{
    Vector3Df v1(1, 0, 0);

    Vector3Df v2 = v1.rotated(90, Vector3Df(0, 1, 0));
    EXPECT_FLOAT_EQ(0.0f, v2.x);
    EXPECT_FLOAT_EQ(0.0f, v2.y);
    EXPECT_FLOAT_EQ(-1.0f, v2.z);

    Vector3Df v3 = v2.rotated(90, Vector3Df(0, 1, 0));
    EXPECT_FLOAT_EQ(-1.0f, v3.x);
    EXPECT_FLOAT_EQ(0.0f, v3.y);
    EXPECT_FLOAT_EQ(0.0f, v3.z);

    v2 = v3.rotated(90, Vector3Df(0, 1, 0));
    EXPECT_FLOAT_EQ(0.0f, v2.x);
    EXPECT_FLOAT_EQ(0.0f, v2.y);
    EXPECT_FLOAT_EQ(1.0f, v2.z);

    v3 = v1.rotated(90, Vector3Df(0, 1, 0));
    EXPECT_FLOAT_EQ(0.0f, v3.x);
    EXPECT_FLOAT_EQ(0.0f, v3.y);
    EXPECT_FLOAT_EQ(-1.0f, v3.z);
}
