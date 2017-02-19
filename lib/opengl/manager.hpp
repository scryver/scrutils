#ifndef SCRYVER_OPENGL_MANAGER_HPP
#define SCRYVER_OPENGL_MANAGER_HPP

#include <cstdint>
#include <cstddef>
#include <vector>

namespace Scryver {

namespace OpenGL {

typedef uint32_t buffer_t;
typedef uint32_t vertexArray_t;

class GLManager
{
public:
    bool initialize(size_t reserveBuffers = 512, size_t reserveVertexArrays = 128);
    void destroy();

    buffer_t createBuffer();
    std::vector<buffer_t> createBuffers(size_t nrBuffers);
    void bindArrayBuffer(buffer_t buffer);
    void unbindArrayBuffer();
    void bindElementBuffer(buffer_t buffer);
    void unbindElementBuffer();

    vertexArray_t createVertexArray();
    std::vector<vertexArray_t> createVertexArrays(size_t nrVertexArrays);
    void bindVertexArray(vertexArray_t vertexArray);
    void unbindVertexArray();

    static GLManager& getInstance();

    GLManager(const GLManager&) = delete;
    GLManager& operator=(const GLManager&) = delete;

private:
    GLManager();
    ~GLManager();

    std::vector<buffer_t>       m_vBuffers;
    std::vector<vertexArray_t>  m_vVertexArrays;
};

}  // namespace OpenGL

}  // namespace Scryver

#define glManager   Scryver::OpenGL::GLManager::getInstance()

#endif  // SCRYVER_OPENGL_MANAGER_HPP
