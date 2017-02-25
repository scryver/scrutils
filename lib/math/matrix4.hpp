#ifndef SCRYVER_MATH_MATRIX4_HPP
#define SCRYVER_MATH_MATRIX4_HPP

#include <cmath>

#include "Scryver/Math/Vector3D.hpp"
#include "Scryver/Math/Conversions.hpp"

namespace Scryver {

namespace Math {

template <typename N = float>
struct Matrix4
{
    N m[4][4];

    inline Matrix4<N> operator*(const Matrix4<N>& right) const;

    inline void initIdentity();
    inline void initScaling(const Vector3D<N>& scale);
    inline void initScaling(const N& x, const N& y, const N& z);
    inline void initRotation(const Vector3D<N>& rotation);
    inline void initRotation(const N& x, const N& y, const N& z);
    inline void initTranslation(const Vector3D<N>& position);
    inline void initTranslation(const N& x, const N& y, const N& z);
    inline void initPerspective(const N& fov,
                                const N& width, const N& height,
                                const N& near, const N& far);
};

#include "matrix4_inl.hpp"

typedef Matrix4<double>         Matrix4d;
typedef Matrix4<float>          Matrix4f;
typedef Matrix4<int>            Matrix4i;
typedef Matrix4<unsigned int>   Matrix4u;

}  // namespace Math

}  // namespace Scryver

#endif  // SCRYVER_MATH_MATRIX4_HPP
