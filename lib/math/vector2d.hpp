#ifndef SCRYVER_MATH_VECTOR_2D_HPP
#define SCRYVER_MATH_VECTOR_2D_HPP

namespace Scryver {

namespace Math {

template <typename N = float>
struct Vector2D
{
    N x;
    N y;

    inline Vector2D();
    inline explicit Vector2D(const N& both);
    inline Vector2D(const N& x, const N& y);

    inline Vector2D<N>& operator+=(const N& right);
    inline Vector2D<N>& operator+=(const Vector2D<N>& right);
    inline Vector2D<N>& operator-=(const N& right);
    inline Vector2D<N>& operator-=(const Vector2D<N>& right);
};

template <typename N>
inline Vector2D<N> operator+(const Vector2D<N>& left, const N& right);
template <typename N>
inline Vector2D<N> operator+(const N& left, const Vector2D<N>& right);
template <typename N>
inline Vector2D<N> operator+(const Vector2D<N>& left, const Vector2D<N>& right);
template <typename N>
inline Vector2D<N> operator-(const Vector2D<N>& left, const N& right);
template <typename N>
inline Vector2D<N> operator-(const N& left, const Vector2D<N>& right);
template <typename N>
inline Vector2D<N> operator-(const Vector2D<N>& left, const Vector2D<N>& right);
template <typename N>
inline Vector2D<N> operator*(float scalar, const Vector2D<N>& vector);
template <typename N>
inline Vector2D<N> operator*(const Vector2D<N>& vector, float scalar);

// This include only works when the default constructor is already defined
#include "vector2d_inl.hpp"

typedef Vector2D<double>         Vector2Dd;
typedef Vector2D<float>          Vector2Df;
typedef Vector2D<int>            Vector2Di;
typedef Vector2D<unsigned int>   Vector2Du;

}  // namespace Math

}  // namespace Scryver

#endif  // SCRYVER_MATH_VECTOR_2D_HPP
