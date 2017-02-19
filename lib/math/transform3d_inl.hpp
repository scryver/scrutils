template <typename N>
Transform3D<N>::Transform3D()
    : m_scale(1, 1, 1)
    , m_worldPosition()
    , m_rotation()
    , m_transformation()
{
    // Empty
}

template <typename N>
void Transform3D<N>::scale(const Vector3D<N> s)
{
    scale(s.x, s.y, s.z);
}

template <typename N>
void Transform3D<N>::scale(N x, N y, N z)
{
    m_scale.x = x;
    m_scale.y = y;
    m_scale.z = z;
}

template <typename N>
void Transform3D<N>::worldPos(const Vector3D<N> wp)
{
    worldPos(wp.x, wp.y, wp.z);
}

template <typename N>
void Transform3D<N>::worldPos(N x, N y, N z)
{
    m_worldPosition.x = x;
    m_worldPosition.y = y;
    m_worldPosition.z = z;
}

template <typename N>
void Transform3D<N>::rotate(const Vector3D<N> r)
{
    rotate(r.x, r.y, r.z);
}

template <typename N>
void Transform3D<N>::rotate(N x, N y, N z)
{
    m_rotation.x = x;
    m_rotation.y = y;
    m_rotation.z = z;
}

template <typename N>
const Matrix4<N>& Transform3D<N>::get()
{
    Matrix4<N> scale, rotate, translate;
    scale.initScaling(m_scale);
    rotate.initRotation(m_rotation);
    translate.initTranslation(m_worldPosition);
    m_transformation = translate * rotate * scale;
    return m_transformation;
}
