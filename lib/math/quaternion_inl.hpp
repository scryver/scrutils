template <typename N>
Quaternion<N>::Quaternion() :
    Quaternion(0, 0, 0, 0)
{
    // Empty
}

template <typename N>
Quaternion<N>::Quaternion(const N& angleDegree, const Vector3D<N>& rotationAxis)
{
    const N sinHalf = sin(toRadian(angleDegree / 2.0));
    const Vector3D<N> norm = rotationAxis.normalized();

    s = cos(toRadian(angleDegree / 2.0));
    i = norm.x * sinHalf;
    j = norm.y * sinHalf;
    k = norm.z * sinHalf;
}

template <typename N>
Quaternion<N>::Quaternion(const N& s_, const N& i_, const N& j_, const N& k_) :
    s(s_), i(i_), j(j_), k(k_)
{
    // Empty
}

template <typename N>
Quaternion<N> Quaternion<N>::conjugate() const
{
    return Quaternion(s, -i, -j, -k);
}

template <typename N>
Quaternion<N>& Quaternion<N>::operator*=(const Vector3D<N>& right)
{
    const N s_ = -i * right.x - j * right.y - k * right.z;
    const N i_ =  s * right.x + j * right.z - k * right.y;
    const N j_ =  s * right.y + k * right.x - i * right.z;
    const N k_ =  s * right.z + i * right.y - j * right.x;

    s = s_;
    i = i_;
    j = j_;
    k = k_;

    return *this;
}

template <typename N>
Quaternion<N>& Quaternion<N>::operator*=(const Quaternion<N>& right)
{
    const N s_ = s * right.s - i * right.i - j * right.j - k * right.k;
    const N i_ = i * right.s + s * right.i + j * right.k - k * right.j;
    const N j_ = j * right.s + s * right.j + k * right.i - i * right.k;
    const N k_ = k * right.s + s * right.k + i * right.j - j * right.i;

    s = s_;
    i = i_;
    j = j_;
    k = k_;

    return *this;
}

template <typename N>
const Quaternion<N> operator*(const Quaternion<N>& quaternion, const Vector3D<N>& vector)
{
    return Quaternion<N>(quaternion) *= vector;
}

template <typename N>
const Quaternion<N> operator*(const Quaternion<N>& lhs, const Quaternion<N>& rhs)
{
    return Quaternion<N>(lhs) *= rhs;
}

