template <typename N>
Matrix4<N> Matrix4<N>::operator*(const Matrix4<N>& right) const
{
    Matrix4<N> result;

    result.m[0][0] = m[0][0] * right.m[0][0] + m[0][1] * right.m[1][0] + m[0][2] * right.m[2][0] + m[0][3] * right.m[3][0];
    result.m[0][1] = m[0][0] * right.m[0][1] + m[0][1] * right.m[1][1] + m[0][2] * right.m[2][1] + m[0][3] * right.m[3][1];
    result.m[0][2] = m[0][0] * right.m[0][2] + m[0][1] * right.m[1][2] + m[0][2] * right.m[2][2] + m[0][3] * right.m[3][2];
    result.m[0][3] = m[0][0] * right.m[0][3] + m[0][1] * right.m[1][3] + m[0][2] * right.m[2][3] + m[0][3] * right.m[3][3];

    result.m[1][0] = m[1][0] * right.m[0][0] + m[1][1] * right.m[1][0] + m[1][2] * right.m[2][0] + m[1][3] * right.m[3][0];
    result.m[1][1] = m[1][0] * right.m[0][1] + m[1][1] * right.m[1][1] + m[1][2] * right.m[2][1] + m[1][3] * right.m[3][1];
    result.m[1][2] = m[1][0] * right.m[0][2] + m[1][1] * right.m[1][2] + m[1][2] * right.m[2][2] + m[1][3] * right.m[3][2];
    result.m[1][3] = m[1][0] * right.m[0][3] + m[1][1] * right.m[1][3] + m[1][2] * right.m[2][3] + m[1][3] * right.m[3][3];

    result.m[2][0] = m[2][0] * right.m[0][0] + m[2][1] * right.m[1][0] + m[2][2] * right.m[2][0] + m[2][3] * right.m[3][0];
    result.m[2][1] = m[2][0] * right.m[0][1] + m[2][1] * right.m[1][1] + m[2][2] * right.m[2][1] + m[2][3] * right.m[3][1];
    result.m[2][2] = m[2][0] * right.m[0][2] + m[2][1] * right.m[1][2] + m[2][2] * right.m[2][2] + m[2][3] * right.m[3][2];
    result.m[2][3] = m[2][0] * right.m[0][3] + m[2][1] * right.m[1][3] + m[2][2] * right.m[2][3] + m[2][3] * right.m[3][3];

    result.m[3][0] = m[3][0] * right.m[0][0] + m[3][1] * right.m[1][0] + m[3][2] * right.m[2][0] + m[3][3] * right.m[3][0];
    result.m[3][1] = m[3][0] * right.m[0][1] + m[3][1] * right.m[1][1] + m[3][2] * right.m[2][1] + m[3][3] * right.m[3][1];
    result.m[3][2] = m[3][0] * right.m[0][2] + m[3][1] * right.m[1][2] + m[3][2] * right.m[2][2] + m[3][3] * right.m[3][2];
    result.m[3][3] = m[3][0] * right.m[0][3] + m[3][1] * right.m[1][3] + m[3][2] * right.m[2][3] + m[3][3] * right.m[3][3];

    return result;
}

template <typename N>
void Matrix4<N>::initIdentity()
{
    m[0][0] = static_cast<N>(1); m[0][1] = N(); m[0][2] = N(); m[0][3] = N();
    m[1][0] = N(); m[1][1] = static_cast<N>(1); m[1][2] = N(); m[1][3] = N();
    m[2][0] = N(); m[2][1] = N(); m[2][2] = static_cast<N>(1); m[2][3] = N();
    m[3][0] = N(); m[3][1] = N(); m[3][2] = N(); m[3][3] = static_cast<N>(1);
}

template <typename N>
void Matrix4<N>::initScaling(const Vector3D<N>& scale)
{
    initScaling(scale.x, scale.y, scale.z);
}

template <typename N>
void Matrix4<N>::initScaling(const N& x, const N& y, const N& z)
{
    initIdentity();
    m[0][0] = x;
    m[1][1] = y;
    m[2][2] = z;
}

template <typename N>
void Matrix4<N>::initRotation(const Vector3D<N>& rotation)
{
    initRotation(rotation.x, rotation.y, rotation.z);
}

template <typename N>
void Matrix4<N>::initRotation(const N& rotateX, const N& rotateY, const N& rotateZ)
{
    Matrix4<N> rx, ry, rz;

    const N x = toRadian<N>(rotateX);
    const N y = toRadian<N>(rotateY);
    const N z = toRadian<N>(rotateZ);

    rx.initIdentity();
    rx.m[1][1] = cos(x); rx.m[1][2] = -sin(x);
    rx.m[2][1] = sin(x); rx.m[2][2] = cos(x);

    ry.initIdentity();
    ry.m[0][0] = cos(y); ry.m[0][2] = -sin(y);
    ry.m[2][0] = sin(y); ry.m[2][2] = cos(y);

    rz.initIdentity();
    rz.m[0][0] = cos(z); rz.m[0][1] = -sin(z);
    rz.m[1][0] = sin(z); rz.m[1][1] = cos(z);

    *this = rz * ry * rx;
}

template <typename N>
void Matrix4<N>::initTranslation(const Vector3D<N>& position)
{
    initTranslation(position.x, position.y, position.z);
}

template <typename N>
void Matrix4<N>::initTranslation(const N& x, const N& y, const N& z)
{
    initIdentity();
    m[0][3] = x;
    m[1][3] = y;
    m[2][3] = z;
}
