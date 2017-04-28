#ifndef SCRYVER_MATH_CONVERSIONS_HPP
#define SCRYVER_MATH_CONVERSIONS_HPP

#include "Scryver/Math/Constants.hpp"

namespace Scryver {

namespace Math {

template <typename T>
constexpr inline T toRadian(const T& degree) { return degree * PI<T>() / static_cast<T>(180.0); }

template <typename T>
constexpr inline T toDegree(const T& radian) { return radian * static_cast<T>(180.0) / PI<T>(); }

}  // namespace Math

}  // namespace Scryver

#endif  // SCRYVER_MATH_CONVERSIONS_HPP
