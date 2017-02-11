#ifndef SCRYVER_MATH_VECTOR2D_HPP
#define SCRYVER_MATH_VECTOR2D_HPP

namespace Scryver {

namespace Math {

template <typename Number = float>
class Vector2D
{
public:
    inline Vector2D();
    inline explicit Vector2D(const Number& both);
    inline Vector2D(const Number& x, const Number& y);

    Number x;
    Number y;
};

// This include only works when the default constructor is already defined
#include "vector2d.inl"


typedef Vector2D<double>         Vector2Dd;
typedef Vector2D<float>          Vector2Df;
typedef Vector2D<int>            Vector2Di;
typedef Vector2D<unsigned int>   Vector2Du;

}  // namespace Math

}  // namespace Scryver

#endif  // SCRYVER_MATH_VECTOR2D_HPP
