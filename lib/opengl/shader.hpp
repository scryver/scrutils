#ifndef SCRYVER_OPENGL_SHADER_HPP
#define SCRYVER_OPENGL_SHADER_HPP

#include <cstdint>
#include <string>

namespace Scryver {

namespace OpenGL {

typedef uint32_t uniform_t;

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

    uint32_t identifier;
};

}  // namespace OpenGL

}  // namespace Scryver

#endif  // SCRYVER_OPENGL_SHADER_HPP
