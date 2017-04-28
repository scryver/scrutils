#ifndef SCRYVER_OPENGL_SHADER_HPP
#define SCRYVER_OPENGL_SHADER_HPP

#include <cstdint>
#include <string>

#include "Scryver/Math/Matrix4.hpp"
#include "Scryver/Utility/TypeUtils.hpp"

namespace Scryver {

namespace OpenGL {

struct shader_tag{};
typedef Scryver::Utils::ID<shader_tag, uint32_t, 0> shader_t;
struct uniform_tag{};
typedef Scryver::Utils::ID<uniform_tag, uint32_t, 0xFFFFFFFF> uniform_t;

class Shader
{
public:
    Shader();
    ~Shader();

    bool initialize(const std::string& vertex, const std::string& fragment,
                    bool fromFiles = true);
    void destroy();

    void use();

    uniform_t getUniform(const std::string& uniform);

    void uploadUniform(uniform_t location, int value);
    void uploadUniform(uniform_t location, const Scryver::Math::Matrix4f& value,
                       bool transpose = true);

    shader_t identifier;
};

}  // namespace OpenGL

}  // namespace Scryver

#endif  // SCRYVER_OPENGL_SHADER_HPP
