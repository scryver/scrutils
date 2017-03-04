template <typename N>
Vector2D<N>::Vector2D() :
    Vector2D(0, 0)
{

}

template <typename N>
Vector2D<N>::Vector2D(const N& both) :
    Vector2D(both, both)
{

}

template <typename N>
Vector2D<N>::Vector2D(const N& x_, const N& y_) :
    x(x_), y(y_)
{
    // Empty
}

template <typename N>
Vector2D<N>& Vector2D<N>::operator+=(const N& right)
{
    this->x += right;
    this->y += right;

    return *this;
}

template <typename N>
Vector2D<N>& Vector2D<N>::operator+=(const Vector2D<N>& right)
{
    this->x += right.x;
    this->y += right.y;

    return *this;
}

template <typename N>
Vector2D<N>& Vector2D<N>::operator-=(const N& right)
{
    this->x -= right;
    this->y -= right;

    return *this;
}

template <typename N>
Vector2D<N>& Vector2D<N>::operator-=(const Vector2D<N>& right)
{
    this->x -= right.x;
    this->y -= right.y;

    return *this;
}

template <typename N>
inline Vector2D<N> operator+(const Vector2D<N>& left, const N& right)
{
    return Vector2D<N>(left.x + right, left.y + right);
}

template <typename N>
inline Vector2D<N> operator+(const N& left, const Vector2D<N>& right)
{
    return right + left;
}

template <typename N>
Vector2D<N> operator+(const Vector2D<N>& left, const Vector2D<N>& right)
{
    return Vector2D<N>(left.x + right.x, left.y + right.y);
}

template <typename N>
inline Vector2D<N> operator-(const Vector2D<N>& left, const N& right)
{
    return Vector2D<N>(left.x - right, left.y - right);
}

template <typename N>
inline Vector2D<N> operator-(const N& left, const Vector2D<N>& right)
{
    return Vector2D<N>(left - right.x, left - right.y);
}

template <typename N>
Vector2D<N> operator-(const Vector2D<N>& left, const Vector2D<N>& right)
{
    return Vector2D<N>(left.x - right.x, left.y - right.y);
}

template <typename N>
Vector2D<N> operator*(float scalar, const Vector2D<N>& vector)
{
    return Vector2D<N>(scalar * vector.x, scalar * vector.y);
}

template <typename N>
Vector2D<N> operator*(const Vector2D<N>& vector, float scalar)
{
    return scalar * vector;
}
