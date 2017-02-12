#ifndef SCRYVER_OPENGL_SHADER_HPP
#define SCRYVER_OPENGL_SHADER_HPP

#include <cstdint>
#include <string>

namespace Scryver {

namespace OpenGL {

class Shader
{
public:
    Shader();
    ~Shader();

    bool initialize(const std::string& vertex, const std::string& fragment,
                    bool fromFiles = true);
    void destroy();

    uint32_t identifier;
};

}  // namespace OpenGL

}  // namespace Scryver

#endif  // SCRYVER_OPENGL_SHADER_HPP
