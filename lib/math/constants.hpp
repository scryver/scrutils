#ifndef SCRYVER_MATH_CONSTANTS_HPP
#define SCRYVER_MATH_CONSTANTS_HPP

namespace Scryver {

namespace Math {

const float     fPI = 3.141592653589793116f;
const float     fPIdiv2 = fPI / 2.0f;
const float     fPIdiv3 = fPI / 3.0f;
const float     fPIdiv4 = fPI / 4.0f;
const float     f2PI = fPI * 2.0f;

const double    dPI = 3.141592653589793115997963468544185161591;
const double    dPIdiv2 = dPI / 2.0;
const double    dPIdiv3 = dPI / 3.0;
const double    dPIdiv4 = dPI / 4.0;
const double    d2PI = dPI * 2.0;

template <typename T = float>
inline T PI() { return static_cast<T>(dPI); }

}  // namespace Math

}  // namespace Scryver

#endif  // SCRYVER_MATH_CONSTANTS_HPP
