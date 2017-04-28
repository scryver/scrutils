template <typename N>
Transform3D<N>::Transform3D()
    : m_scale(1, 1, 1)
    , m_rotation()
    , m_worldPosition()
    , m_transformation()
{
    // Empty
}

template <typename N>
Transform3D<N>::Transform3D(const Vector3D<N>& scale,
                            const Vector3D<N>& rotate,
                            const Vector3D<N>& position)
    : m_scale(scale)
    , m_rotation(rotate)
    , m_worldPosition(position)
    , m_transformation()
{
    // Empty
}

template <typename N>
const Vector3D<N>& Transform3D<N>::scale() const
{
    return m_scale;
}

template <typename N>
void Transform3D<N>::scale(const Vector3D<N>& s)
{
    scale(s.x, s.y, s.z);
}

template <typename N>
void Transform3D<N>::scale(const N& x, const N& y, const N& z)
{
    m_dirty = true;
    m_scale.x = x;
    m_scale.y = y;
    m_scale.z = z;
}

template <typename N>
const Vector3D<N>& Transform3D<N>::rotate() const
{
    return m_rotation;
}

template <typename N>
void Transform3D<N>::rotate(const Vector3D<N>& r)
{
    rotate(r.x, r.y, r.z);
}

template <typename N>
void Transform3D<N>::rotate(const N& x, const N& y, const N& z)
{
    m_dirty = true;
    m_rotation.x = x;
    m_rotation.y = y;
    m_rotation.z = z;
}

template <typename N>
const Vector3D<N>& Transform3D<N>::worldPos() const
{
    return m_worldPosition;
}

template <typename N>
void Transform3D<N>::worldPos(const Vector3D<N>& wp)
{
    worldPos(wp.x, wp.y, wp.z);
}

template <typename N>
void Transform3D<N>::worldPos(const N& x, const N& y, const N& z)
{
    m_dirty = true;
    m_worldPosition.x = x;
    m_worldPosition.y = y;
    m_worldPosition.z = z;
}

template <typename N>
const Matrix4<N>& Transform3D<N>::get()
{
    if (m_dirty)
    {
        Matrix4<N> scale, rotate, translate;
        scale.initScaling(m_scale);
        rotate.initRotation(m_rotation);
        translate.initTranslation(m_worldPosition);
        m_transformation = translate * rotate * scale;
        m_dirty = false;
    }
    return m_transformation;
}
