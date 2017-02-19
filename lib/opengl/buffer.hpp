#ifndef SCRYVER_OPENGL_BUFFER_HPP
#define SCRYVER_OPENGL_BUFFER_HPP

#include <cstdint>

#include <vector>

#ifndef TEST
#include <GL/glew.h>
#endif

#include "Scryver/Utility/Macros.hpp"

namespace Scryver {

namespace OpenGL {

class Buffer
{
public:
    enum BufferType {
        ArrayBuffer = GL_ARRAY_BUFFER,
        ElementBuffer = GL_ELEMENT_BUFFER,
    };

    enum BufferMode {
        Static = GL_STATIC_DRAW,
        Dynamic = GL_DYNAMIC_DRAW,
        Stream,
    };

    Buffer() : identifier(0), type(GL_ARRAY_BUFFER), mode(GL_STATIC_DRAW) { }
    ~Buffer() { destroy(); }

    inline bool initialize()   {
        if (identifier == 0)
        {
            glGenBuffers(1, &identifier);
            return true;
        }
        return false;
    }
    inline void destroy()      { if (identifier != 0) glDeleteBuffers(1, &identifier); }

    template <typename T>
    bool initialize(const std::vector<T>& data,
                    BufferType type = ArrayBuffer,
                    BufferMode mode = Static);


    template <typename T>
    uint32_t bufferData(const std::vector<T>& data,
                        BufferType type = ArrayBuffer,
                        BufferMode mode = Static);
    uint32_t bufferFloatData(const std::vector<float>& data,
                             BufferType type = ArrayBuffer,
                             BufferMode mode = Static) { return bufferData<float>(data, type, mode); }

    inline void bind() const { glBindBuffer(type, identifier); }
    inline void unbind() const { glBindBuffer(type, 0); }

    static void unbind(BufferType type)
    {
        if (type == ArrayBuffer)
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        else if (type == ElementBuffer)
            glBindBuffer(GL_ELEMENT_BUFFER, 0);
    }

    uint32_t identifier;
    GLenum type;
    GLenum mode;
};

#include "buffer_inl.hpp"

}  // namespace OpenGL

}  // namespace Scryver

#endif  // SCRYVER_OPENGL_BUFFER_HPP
