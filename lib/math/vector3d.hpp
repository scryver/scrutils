#ifndef SCRYVER_MATH_VECTOR_3D_HPP
#define SCRYVER_MATH_VECTOR_3D_HPP

#include <cmath>

#include "Scryver/Math/Conversions.hpp"

namespace Scryver {

namespace Math {

template <typename N>
struct Quaternion;

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

    inline Vector3D<N> cross(const Vector3D<N>& right) const;

    inline Vector3D<N> rotated(const N& angleDegree, const Vector3D<N>& rotationAxis) const;
    inline Vector3D<N> rotated(const Quaternion<N>& rotor) const;
    inline Vector3D<N>& rotate(const N& angleDegree, const Vector3D<N>& rotationAxis);
    inline Vector3D<N>& rotate(const Quaternion<N>& rotor);

    inline Vector3D<N> operator-() const;
    inline Vector3D<N>& operator+=(const N& right);
    inline Vector3D<N>& operator+=(const Vector3D<N>& right);
    inline Vector3D<N>& operator-=(const N& right);
    inline Vector3D<N>& operator-=(const Vector3D<N>& right);
    inline Vector3D<N>& operator*=(const N& right);
};

template <typename N = float>
struct Quaternion
{
    N       s;
    N       i;
    N       j;
    N       k;

    inline Quaternion();
    inline Quaternion(const N& angleDegree, const Vector3D<N>& rotationAxis);
    inline Quaternion(const N& s, const N& i, const N& j, const N& k);

    inline Quaternion<N> conjugate() const;

    inline Quaternion<N>& operator*=(const Vector3D<N>& right);
    inline Quaternion<N>& operator*=(const Quaternion<N>& right);
};

// template <typename N>
// inline const Vector3D<N> operator-(const Vector3D<N>& vector);
template <typename N>
inline const Vector3D<N> operator+(const Vector3D<N>& left, const N& right);
template <typename N>
inline const Vector3D<N> operator+(const N& left, const Vector3D<N>& right);
template <typename N>
inline const Vector3D<N> operator+(const Vector3D<N>& left, const Vector3D<N>& right);
template <typename N>
inline const Vector3D<N> operator-(const Vector3D<N>& left, const N& right);
template <typename N>
inline const Vector3D<N> operator-(const N& left, const Vector3D<N>& right);
template <typename N>
inline const Vector3D<N> operator-(const Vector3D<N>& left, const Vector3D<N>& right);
template <typename N>
inline const Vector3D<N> operator*(float scalar, const Vector3D<N>& vector);
template <typename N>
inline const Vector3D<N> operator*(const Vector3D<N>& vector, float scalar);

template <typename N>
inline const Quaternion<N> operator*(const Quaternion<N>& quaternion, const Vector3D<N>& vector);
template <typename N>
inline const Quaternion<N> operator*(const Quaternion<N>& lhs, const Quaternion<N>& rhs);

// This include only works when the default constructor is already defined
#include "vector3d_inl.hpp"
#include "quaternion_inl.hpp"

typedef Vector3D<double>            Vector3Dd;
typedef Vector3D<float>             Vector3Df;
typedef Vector3D<int>               Vector3Di;
typedef Vector3D<unsigned int>      Vector3Du;

typedef Quaternion<double>          Quaterniond;
typedef Quaternion<float>           Quaternionf;
typedef Quaternion<int>             Quaternioni;
typedef Quaternion<unsigned int>    Quaternionu;

}  // namespace Math

}  // namespace Scryver

#endif  // SCRYVER_MATH_VECTOR_3D_HPP
