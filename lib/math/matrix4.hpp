#ifndef SCRYVER_MATH_MATRIX4_HPP
#define SCRYVER_MATH_MATRIX4_HPP

namespace Scryver {

namespace Math {

template <typename N = float>
struct Matrix4
{
    N m[4][4];
};

typedef Matrix4<double>         Matrix4d;
typedef Matrix4<float>          Matrix4f;
typedef Matrix4<int>            Matrix4i;
typedef Matrix4<unsigned int>   Matrix4u;

}  // namespace Math

}  // namespace Scryver

#endif  // SCRYVER_MATH_MATRIX4_HPP
