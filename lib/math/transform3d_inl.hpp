template <typename N>
Transform3D<N>::Transform3D()
    : m_scale()
    , m_worldPosition()
    , m_rotation()
    , m_transformation()
{

}

template <typename N>
Transform3D<N>::~Transform3D()
{
    destroy();
}

template <typename N>
bool Transform3D<N>::initialize()
{
    m_scale = Vector3D<N>();
    m_worldPosition = Vector3D<N>();
    m_rotation = Vector3D<N>();
    m_transformation = Matrix4<N>();
    return true;
}

template <typename N>
void Transform3D<N>::destroy()
{
    // Empty
}

template <typename N>
void Transform3D<N>::scale(const Vector3D<N> s)
{

}

template <typename N>
void Transform3D<N>::scale(N x, N y, N z)
{

}

template <typename N>
void Transform3D<N>::worldPos(const Vector3D<N> s)
{

}

template <typename N>
void Transform3D<N>::worldPos(N x, N y, N z)
{

}

template <typename N>
void Transform3D<N>::rotate(const Vector3D<N> s)
{

}

template <typename N>
void Transform3D<N>::rotate(N x, N y, N z)
{

}

template <typename N>
const Matrix4<N>* Transform3D<N>::get()
{
    return &m_transformation;
}
