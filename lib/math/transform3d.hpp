#ifndef SCRYVER_MATH_TRANSFORM_HPP
#define SCRYVER_MATH_TRANSFORM_HPP

#include "Scryver/Math/Vector3D.hpp"
#include "Scryver/Math/Matrix4.hpp"

namespace Scryver {

namespace Math {

template <typename N = float>
class Transform3D
{
public:
    Transform3D();
    ~Transform3D();

    bool initialize();
    void destroy();

    void scale(const Vector3D<N> s);
    void scale(N x, N y, N z);

    void worldPos(const Vector3D<N> s);
    void worldPos(N x, N y, N z);

    void rotate(const Vector3D<N> s);
    void rotate(N x, N y, N z);

    const Matrix4<N>* get();

private:
    Vector3D<N>     m_scale;
    Vector3D<N>     m_worldPosition;
    Vector3D<N>     m_rotation;
    Matrix4<N>      m_transformation;
};

#include "transform3d_inl.hpp"

typedef Transform3D<double>         Transform3Dd;
typedef Transform3D<float>          Transform3Df;
typedef Transform3D<int>            Transform3Di;
typedef Transform3D<unsigned int>   Transform3Du;

}  // namespace Math

}  // namespace Scryver

#endif  // SCRYVER_MATH_TRANSFORM_HPP
