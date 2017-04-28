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
    inline Transform3D();
    inline Transform3D(const Vector3D<N>& scale,
                       const Vector3D<N>& rotate,
                       const Vector3D<N>& position);

    inline const Vector3D<N>& scale() const;
    inline void scale(const Vector3D<N>& s);
    inline void scale(const N& x, const N& y, const N& z);

    inline const Vector3D<N>& rotate() const;
    inline void rotate(const Vector3D<N>& r);
    inline void rotate(const N& x, const N& y, const N& z);

    inline const Vector3D<N>& worldPos() const;
    inline void worldPos(const Vector3D<N>& wp);
    inline void worldPos(const N& x, const N& y, const N& z);

    inline const Matrix4<N>& get();

private:
    Vector3D<N>     m_scale;
    Vector3D<N>     m_rotation;
    Vector3D<N>     m_worldPosition;
    Matrix4<N>      m_transformation;

    bool            m_dirty{true};
};

#include "transform3d_inl.hpp"

typedef Transform3D<double>         Transform3Dd;
typedef Transform3D<float>          Transform3Df;
typedef Transform3D<int>            Transform3Di;
typedef Transform3D<unsigned int>   Transform3Du;

}  // namespace Math

}  // namespace Scryver

#endif  // SCRYVER_MATH_TRANSFORM_HPP
