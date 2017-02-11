template <typename N>
Vector3D<N>::Vector3D() :
    Vector3D(0, 0, 0)
{

}

template <typename N>
Vector3D<N>::Vector3D(const N& all) :
    Vector3D(all, all, all)
{

}

template <typename N>
Vector3D<N>::Vector3D(const N& x_, const N& y_, const N& z_) :
    x(x_), y(y_), z(z_)
{
    // Empty
}

template <typename N>
Vector3D<N>& Vector3D<N>::operator+=(const N& right)
{
    this->x += right;
    this->y += right;
    this->z += right;

    return *this;
}

template <typename N>
Vector3D<N>& Vector3D<N>::operator+=(const Vector3D<N>& right)
{
    this->x += right.x;
    this->y += right.y;
    this->z += right.z;

    return *this;
}

template <typename N>
Vector3D<N>& Vector3D<N>::operator-=(const N& right)
{
    this->x -= right;
    this->y -= right;
    this->z -= right;

    return *this;
}

template <typename N>
Vector3D<N>& Vector3D<N>::operator-=(const Vector3D<N>& right)
{
    this->x -= right.x;
    this->y -= right.y;
    this->z -= right.z;

    return *this;
}

template <typename N>
inline Vector3D<N> operator+(const Vector3D<N>& left, const N& right)
{
    return Vector3D<N>(left.x + right, left.y + right, left.z + right);
}

template <typename N>
inline Vector3D<N> operator+(const N& left, const Vector3D<N>& right)
{
    return right + left;
}

template <typename N>
Vector3D<N> operator+(const Vector3D<N>& left, const Vector3D<N>& right)
{
    return Vector3D<N>(left.x + right.x, left.y + right.y, left.z + right.z);
}

template <typename N>
inline Vector3D<N> operator-(const Vector3D<N>& left, const N& right)
{
    return Vector3D<N>(left.x - right, left.y - right, left.z - right);
}

template <typename N>
inline Vector3D<N> operator-(const N& left, const Vector3D<N>& right)
{
    return Vector3D<N>(left - right.x, left - right.y, left - right.z);
}

template <typename N>
Vector3D<N> operator-(const Vector3D<N>& left, const Vector3D<N>& right)
{
    return Vector3D<N>(left.x - right.x, left.y - right.y, left.z - right.z);
}

template <typename N>
Vector3D<N> operator*(float scalar, const Vector3D<N>& vector)
{
    return Vector3D<N>(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}

template <typename N>
Vector3D<N> operator*(const Vector3D<N>& vector, float scalar)
{
    return scalar * vector;
}
