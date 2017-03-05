#ifndef SCRYVER_OPENGL_MANAGER_HPP
#define SCRYVER_OPENGL_MANAGER_HPP

#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>

namespace Scryver {

namespace OpenGL {

typedef uint32_t buffer_t;
typedef uint32_t vertexArray_t;
typedef uint32_t texture_t;

class GLManager
{
public:
    bool initialize(size_t reserveBuffers = 512,
                    size_t reserveVertexArrays = 128,
                    size_t reserveTextures = 128,
                    bool depthTest = false);
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

    texture_t createTexture(const std::string& ddsPath);
    void bindTexture(texture_t texture);
    void unbindTexture();
    texture_t createSkyBox(const std::string& skyBoxFolderPath);
    void bindSkyBox(texture_t skyBox);
    void unbindSkyBox();

    bool wireMode() const;
    void wireMode(bool on);

    void viewport(uint16_t width, uint16_t height);

    static GLManager& getInstance();

    GLManager(const GLManager&) = delete;
    GLManager& operator=(const GLManager&) = delete;

private:
    GLManager();
    ~GLManager();

    std::vector<buffer_t>       m_vBuffers;
    std::vector<vertexArray_t>  m_vVertexArrays;
    std::vector<texture_t>      m_vTextures;

    bool                        m_wireMode;

    struct ImageData
    {
        unsigned int format;
        unsigned int mipMapCount;
        unsigned int width;
        unsigned int height;
        unsigned char* buffer;
    };

    bool openDdsImage(const std::string& file, ImageData* output);
};

}  // namespace OpenGL

}  // namespace Scryver

#define glManager   Scryver::OpenGL::GLManager::getInstance()

#endif  // SCRYVER_OPENGL_MANAGER_HPP
