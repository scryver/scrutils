#ifndef SCRYVER_MATH_VECTOR_3D_HPP
#define SCRYVER_MATH_VECTOR_3D_HPP

#include <cmath>

namespace Scryver {

namespace Math {

template <typename N = float>
struct Vector3D
{
    N x;
    N y;
    N z;

    inline Vector3D();
    inline explicit Vector3D(const N& all);
    inline Vector3D(const N& x, const N& y, const N& z);

    inline N length() const;
    inline N lengthSquared() const;

    inline Vector3D<N> normalized() const;
    inline Vector3D<N>& normalize();

    inline Vector3D<N> cross(const Vector3D<N>& right);

    inline Vector3D<N>& operator+=(const N& right);
    inline Vector3D<N>& operator+=(const Vector3D<N>& right);
    inline Vector3D<N>& operator-=(const N& right);
    inline Vector3D<N>& operator-=(const Vector3D<N>& right);
};

template <typename N>
inline Vector3D<N> operator+(const Vector3D<N>& left, const N& right);
template <typename N>
inline Vector3D<N> operator+(const N& left, const Vector3D<N>& right);
template <typename N>
inline Vector3D<N> operator+(const Vector3D<N>& left, const Vector3D<N>& right);
template <typename N>
inline Vector3D<N> operator-(const Vector3D<N>& left, const N& right);
template <typename N>
inline Vector3D<N> operator-(const N& left, const Vector3D<N>& right);
template <typename N>
inline Vector3D<N> operator-(const Vector3D<N>& left, const Vector3D<N>& right);
template <typename N>
inline Vector3D<N> operator*(float scalar, const Vector3D<N>& vector);
template <typename N>
inline Vector3D<N> operator*(const Vector3D<N>& vector, float scalar);

// This include only works when the default constructor is already defined
#include "vector3d.inl"

typedef Vector3D<double>         Vector3Dd;
typedef Vector3D<float>          Vector3Df;
typedef Vector3D<int>            Vector3Di;
typedef Vector3D<unsigned int>   Vector3Du;

}  // namespace Math

}  // namespace Scryver

#endif  // SCRYVER_MATH_VECTOR_3D_HPP
