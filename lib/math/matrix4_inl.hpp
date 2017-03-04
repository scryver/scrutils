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

template <typename N>
void Matrix4<N>::initPerspective(const N& fov,
                                 const N& width, const N& height,
                                 const N& near, const N& far)
{
    const N aspectRatio = width / height;
    const N depthRange = near - far;
    const N tanHalfFOV = tan(toRadian(fov / 2.0));
    initIdentity();
    m[0][0] = 1.0 / (tanHalfFOV * aspectRatio);
    m[1][1] = 1.0 / tanHalfFOV;
    m[2][2] = (-near - far) / depthRange;
    m[2][3] = 2.0 * far * near / depthRange;
    m[3][2] = 1.0;
    m[3][3] = 0.0;
}

template <typename Nr>
void Matrix4<Nr>::initLookAt(const Vector3D<Nr>& target,
                             const Vector3D<Nr>& up)
{
    Vector3D<Nr> N = target.normalized();
    Vector3D<Nr> U = up.cross(N);
    U.normalize();
    Vector3D<Nr> V = N.cross(U);

    m[0][0] = U.x;  m[0][1] = U.y;  m[0][2] = U.z;  m[0][3] = 0.0f;
    m[1][0] = V.x;  m[1][1] = V.y;  m[1][2] = V.z;  m[1][3] = 0.0f;
    m[2][0] = N.x;  m[2][1] = N.y;  m[2][2] = N.z;  m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}
