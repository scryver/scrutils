#include "camera.hpp"

#include <cassert>
#include <cmath>

#include "Scryver/Math/Conversions.hpp"
#include "Scryver/Math/Matrix4.hpp"
#include "Scryver/Math/Vector3D.hpp"

using Scryver::Render::Camera;
using Scryver::Math::Vector3Df;
using Scryver::Math::Matrix4f;

Camera::Camera()
{
    m_projection.initIdentity();
    m_viewTarget.initIdentity();
    m_viewPosition.initIdentity();
    m_transform.initIdentity();
}

Camera::~Camera()
{
    destroy();
}

bool Camera::initialize(const Vector3Df& position,
                        const Vector3Df& lookAt,
                        const Vector3Df& up,
                        float width, float height,
                        float fieldOfView, float near, float far)
{
    assert(!(lookAt.x == 0 && lookAt.y == 0 && lookAt.z == 0));
    m_position = position;
    m_lookAtTarget = lookAt;
    m_upDirection = up;
    // calculateProjection();
    m_projection.initPerspective(fieldOfView, width, height, near, far);
    calculateViewTarget();
    calculateViewPosition();
    m_transform = m_projection * m_viewTarget * m_viewPosition;

    Vector3Df hTarget(m_lookAtTarget.x, 0.0, m_lookAtTarget.z);
    hTarget.normalize();

    if (hTarget.z >= 0.0f)
    {
        if (hTarget.x >= 0.0f)
            m_angleHorizontal = 360.0f - Scryver::Math::toDegree(asin(hTarget.z));
        else
            m_angleHorizontal = 180.0f - Scryver::Math::toDegree(asin(hTarget.z));
    }
    else
    {
        if (hTarget.x >= 0.0f)
            m_angleHorizontal = Scryver::Math::toDegree(asin(-hTarget.z));
        else
            m_angleHorizontal = 180.0f - Scryver::Math::toDegree(asin(-hTarget.z));
    }

    m_angleVertical = -Scryver::Math::toDegree(asin(m_lookAtTarget.y));

    // Matrix4f view_translate, view_rotate, projection;
    // projection.initPerspective(fieldOfView, width, height, near, far);
    // view_translate.initTranslation(-position.x, -position.y, -position.z);
    // view_rotate.initLookAt(lookAt, up);
    // m_viewProjection = projection * view_rotate * view_translate;
    return true;
}

void Camera::destroy()
{
    // Empty
}

const Vector3Df& Camera::position() const
{
    return m_position;
}

void Camera::position(const Vector3Df& p)
{
    m_position = p;
    calculateViewPosition();
    m_transform = m_projection * m_viewTarget * m_viewPosition;
}

const Vector3Df& Camera::target() const
{
    return m_lookAtTarget;
}

void Camera::target(const Vector3Df& t)
{
    m_lookAtTarget = t.normalized();
    calculateViewTarget();
    m_transform = m_projection * m_viewTarget * m_viewPosition;
}

const Vector3Df& Camera::up() const
{
    return m_upDirection;
}

void Camera::up(const Vector3Df& u)
{
    m_upDirection = u.normalized();
    calculateViewTarget();
    m_transform = m_projection * m_viewTarget * m_viewPosition;
}

void Camera::calculateViewTarget()
{
    m_viewTarget.initLookAt(m_lookAtTarget, m_upDirection);
}

void Camera::calculateViewPosition()
{
    m_viewPosition.initTranslation(-m_position.x, -m_position.y, -m_position.z);
}
