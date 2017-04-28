#ifndef SCRYVER_MATH_CONSTANTS_HPP
#define SCRYVER_MATH_CONSTANTS_HPP

namespace Scryver {

namespace Math {

constexpr float     fPI = 3.141592653589793116f;
constexpr float     fPIdiv2 = fPI / 2.0f;
constexpr float     fPIdiv3 = fPI / 3.0f;
constexpr float     fPIdiv4 = fPI / 4.0f;
constexpr float     f2PI = fPI * 2.0f;

constexpr double    dPI = 3.141592653589793115997963468544185161591;
constexpr double    dPIdiv2 = dPI / 2.0;
constexpr double    dPIdiv3 = dPI / 3.0;
constexpr double    dPIdiv4 = dPI / 4.0;
constexpr double    d2PI = dPI * 2.0;

template <typename T = float>
constexpr inline const T PI() { return static_cast<T>(dPI); }

}  // namespace Math

}  // namespace Scryver

#endif  // SCRYVER_MATH_CONSTANTS_HPP
