#include <gtest/gtest.h>

#include "Scryver/Math/Transform3D.hpp"

using Scryver::Math::Transform3Df;


TEST(Transform, Constructor)
{
    Transform3Df transform;
    ASSERT_FLOAT_EQ(1.0f, transform.get().m[0][0]);
}
