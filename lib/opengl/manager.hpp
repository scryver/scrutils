#ifndef SCRYVER_OPENGL_MANAGER_HPP
#define SCRYVER_OPENGL_MANAGER_HPP

#include <cstdint>
#include <cstddef>
#include <vector>

namespace Scryver {

namespace OpenGL {

class GLManager
{
public:
    bool initialize();
    void destroy();

    uint32_t createBuffer();
    std::vector<uint32_t> createBuffers(size_t nrBuffers);

    uint32_t createVertexArray();
    std::vector<uint32_t> createVertexArrays(size_t nrVertexArrays);

    static GLManager& getInstance();

    GLManager(const GLManager&) = delete;
    GLManager& operator=(const GLManager&) = delete;

private:
    GLManager();
    ~GLManager();

    std::vector<uint32_t>   m_vBuffers;
    std::vector<uint32_t>   m_vVertexArrays;
};

}  // namespace OpenGL

}  // namespace Scryver

#define glManager   Scryver::OpenGL::GLManager::getInstance()

#endif  // SCRYVER_OPENGL_MANAGER_HPP
