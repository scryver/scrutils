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
N Vector3D<N>::length() const
{
    return sqrt(lengthSquared());
}

template <typename N>
N Vector3D<N>::lengthSquared() const
{
    const N x2 = x * x;
    const N y2 = y * y;
    const N z2 = z * z;
    return x2 + y2 + z2;
}

template <typename N>
Vector3D<N> Vector3D<N>::normalized() const
{
    Vector3D<N> norm(x, y, z);
    norm.normalize();
    return norm;
}

template <typename N>
Vector3D<N>& Vector3D<N>::normalize()
{
    if (lengthSquared() == static_cast<N>(1))
        return *this;

    const N l = length();
    x /= l;
    y /= l;
    z /= l;
    return *this;
}

template <typename N>
Vector3D<N> Vector3D<N>::cross(const Vector3D<N>& right) const
{
    const N newX = y * right.z - z * right.y;
    const N newY = z * right.x - x * right.z;
    const N newZ = x * right.y - y * right.x;
    return Vector3D<N>(newX, newY, newZ);
}

template <typename N>
Vector3D<N>& Vector3D<N>::rotate(const N& angleDegree, const Vector3D<N>& rotationAxis)
{
    return rotate(Quaternion<N>(angleDegree, rotationAxis));
}

template <typename N>
Vector3D<N>& Vector3D<N>::rotate(const Quaternion<N>& rotor)
{
    const Quaternion<N> rotated = rotor * (*this) * rotor.conjugate();
    x = rotated.i;
    y = rotated.j;
    z = rotated.k;

    return *this;
}

template <typename N>
Vector3D<N> Vector3D<N>::operator-() const
{
    return Vector3D<N>(-x, -y, -z);
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
Vector3D<N>& Vector3D<N>::operator*=(const N& right)
{
    this->x *= right;
    this->y *= right;
    this->z  *= right;

    return *this;
}

template <typename N>
const Vector3D<N> operator-(const Vector3D<N>& vector)
{
    return -Vector3D<N>(vector);
}

template <typename N>
const Vector3D<N> operator+(const Vector3D<N>& left, const N& right)
{
    return Vector3D<N>(left) += right;
    // return Vector3D<N>(left.x + right, left.y + right, left.z + right);
}

template <typename N>
const Vector3D<N> operator+(const N& left, const Vector3D<N>& right)
{
    return Vector3D<N>(right) += left;
    // return right + left;
}

template <typename N>
const Vector3D<N> operator+(const Vector3D<N>& left, const Vector3D<N>& right)
{
    return Vector3D<N>(left) += right;
    // return Vector3D<N>(left.x + right.x, left.y + right.y, left.z + right.z);
}

template <typename N>
const Vector3D<N> operator-(const Vector3D<N>& left, const N& right)
{
    return Vector3D<N>(left) -= right;
    // return Vector3D<N>(left.x - right, left.y - right, left.z - right);
}

template <typename N>
const Vector3D<N> operator-(const N& left, const Vector3D<N>& right)
{
    return Vector3D<N>(-right) += left;
    // return Vector3D<N>(left - right.x, left - right.y, left - right.z);
}

template <typename N>
const Vector3D<N> operator-(const Vector3D<N>& left, const Vector3D<N>& right)
{
    return Vector3D<N>(left) -= right;
    // return Vector3D<N>(left.x - right.x, left.y - right.y, left.z - right.z);
}

template <typename N>
const Vector3D<N> operator*(float scalar, const Vector3D<N>& vector)
{
    return Vector3D<N>(vector) *= scalar;
    // return Vector3D<N>(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}

template <typename N>
const Vector3D<N> operator*(const Vector3D<N>& vector, float scalar)
{
    return Vector3D<N>(vector) *= scalar;
    // return scalar * vector;
}
