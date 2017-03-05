#ifndef SCRYVER_RENDER_CAMERA_HPP
#define SCRYVER_RENDER_CAMERA_HPP

#include "Scryver/Math/Matrix4.hpp"
#include "Scryver/Math/Vector2D.hpp"
#include "Scryver/Math/Vector3D.hpp"

namespace Scryver {

namespace Render {

struct ProjectionInfo
{
    float width;
    float height;
    float fieldOfView;
    float near;
    float far;
};

class Camera
{
public:
    Camera();
    ~Camera();

    bool initialize(const Math::Vector3Df& position,
                    const Math::Vector3Df& lookAt,
                    const Math::Vector3Df& up,
                    float width, float height,
                    float fieldOfView = 60.0f,
                    float near = 0.1f, float far = 100.0f);
    void destroy();

    void screenSize(const Math::Vector2Df& size);
    void screenSize(float width, float height);

    const Math::Vector3Df& position() const;
    void position(const Math::Vector3Df& p);
    const Math::Vector3Df& target() const;
    void target(const Math::Vector3Df& t);
    const Math::Vector3Df& up() const;
    void up(const Math::Vector3Df& u);

    const Math::Matrix4f& getWorldViewProjection() const { return m_transform; }
    const Math::Matrix4f& getViewProjection() const { return m_viewProjection; }
    const Math::Matrix4f& getProjection() const { return m_projection; }

private:
    ProjectionInfo  m_projectionInfo;

    Math::Vector3Df m_position;
    Math::Vector3Df m_lookAtTarget;
    Math::Vector3Df m_upDirection;

    Math::Matrix4f  m_viewTarget;
    Math::Matrix4f  m_viewPosition;

    Math::Matrix4f  m_projection;
    Math::Matrix4f  m_viewProjection;
    Math::Matrix4f  m_transform;

    float           m_angleHorizontal;
    float           m_angleVertical;

    void calculateProjection();
    void calculateViewTarget();
    void calculateViewPosition();
};

}  // namespace Render

}  // namespace Scryver

#endif  // SCRYVER_RENDER_CAMERA_HPP
