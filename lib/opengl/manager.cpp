#include "manager.hpp"

#include <cassert>
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

#ifndef TESTING_ENABLED
#include <GL/glew.h>
#else
#include "../../test/lib/opengl/glmock.hpp"
#endif

#include "Scryver/Debug/Printer.hpp"

using Scryver::OpenGL::GLManager;
using Scryver::OpenGL::buffer_t;
using Scryver::OpenGL::vertexArray_t;
using Scryver::OpenGL::texture_t;

#ifndef TESTING_ENABLED
// The ARB_debug_output extension, which is used in this tutorial as an example,
// can call a function of ours with error messages.
// This function must have this precise prototype ( parameters and return value )
// See http://www.opengl.org/registry/specs/ARB/debug_output.txt , "New Types" :
//  The callback function that applications can define, and
//  is accepted by DebugMessageCallbackARB, is defined as:
//
//      typedef void (APIENTRY *DEBUGPROCARB)(enum source,
//                                            enum type,
//                                            uint id,
//                                            enum severity,
//                                            sizei length,
//                                            const char* message,
//                                            void* userParam);
static void DebugOutputCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    if (source == GL_DEBUG_SOURCE_API_ARB && type == GL_DEBUG_TYPE_OTHER_ARB)
    {
        size_t pos = std::string(message).find("will use VIDEO memory as the source for buffer object operati");
        if (pos != std::string::npos)
            return;
    }

    std::cout << "OpenGL Debug Output message : ";

    if(source == GL_DEBUG_SOURCE_API_ARB)                   std::cout << "Source : API; ";
    else if(source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)    std::cout << "Source : WINDOW_SYSTEM; ";
    else if(source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)  std::cout << "Source : SHADER_COMPILER; ";
    else if(source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)      std::cout << "Source : THIRD_PARTY; ";
    else if(source == GL_DEBUG_SOURCE_APPLICATION_ARB)      std::cout << "Source : APPLICATION; ";
    else if(source == GL_DEBUG_SOURCE_OTHER_ARB)            std::cout << "Source : OTHER; ";

    if(type == GL_DEBUG_TYPE_ERROR_ARB)                     std::cout << "Type : ERROR; ";
    else if(type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB)  std::cout << "Type : DEPRECATED_BEHAVIOR; ";
    else if(type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB)   std::cout << "Type : UNDEFINED_BEHAVIOR; ";
    else if(type == GL_DEBUG_TYPE_PORTABILITY_ARB)          std::cout << "Type : PORTABILITY; ";
    else if(type == GL_DEBUG_TYPE_PERFORMANCE_ARB)          std::cout << "Type : PERFORMANCE; ";
    else if(type == GL_DEBUG_TYPE_OTHER_ARB)                std::cout << "Type : OTHER; ";

    if(severity == GL_DEBUG_SEVERITY_HIGH_ARB)              std::cout << "Severity : HIGH; ";
    else if(severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)       std::cout << "Severity : MEDIUM; ";
    else if(severity == GL_DEBUG_SEVERITY_LOW_ARB)          std::cout << "Severity : LOW; ";

    // You can set a breakpoint here ! Your debugger will stop the program,
    // and the callstack will immediately show you the offending call.
    std::cout << "Message : " << message << std::endl;
}
#endif


GLManager::GLManager()
{

}

GLManager::~GLManager()
{
    destroy();
}

bool GLManager::initialize(size_t reserveBuffers, size_t reserveVertexArrays,
                           size_t reserveTextures)
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        errorPrint("Failed to initialize GLEW!");
        return false;
    }

#ifndef TESTING_ENABLED
    if (GLEW_ARB_debug_output)
    {
        debugPrint("The OpenGL implementation provides debug output. Let's use it !");
        glDebugMessageCallbackARB(&DebugOutputCallback, NULL);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
    }
    else
    {
        debugPrint("ARB_debug_output unavailable. "
                   << "You have to use glGetError() and/or gDebugger to catch mistakes.");
    }
#endif

    m_vBuffers.reserve(reserveBuffers);
    m_vVertexArrays.reserve(reserveVertexArrays);
    m_vTextures.reserve(reserveTextures);

    return true;
}

void GLManager::destroy()
{
    if (m_vTextures.size() > 0)
        glDeleteTextures(m_vTextures.size(), &m_vTextures.front());
    if (m_vVertexArrays.size() > 0)
        glDeleteVertexArrays(m_vVertexArrays.size(), &m_vVertexArrays.front());
    if (m_vBuffers.size() > 0)
        glDeleteBuffers(m_vBuffers.size(), &m_vBuffers.front());
    m_vTextures.clear();
    m_vVertexArrays.clear();
    m_vBuffers.clear();
}

buffer_t GLManager::createBuffer()
{
    buffer_t buf;
    glGenBuffers(1, &buf);
    m_vBuffers.push_back(buf);
    return buf;
}

std::vector<buffer_t> GLManager::createBuffers(size_t nrBuffers)
{
    std::vector<buffer_t> buf;
    buf.resize(nrBuffers);
    glGenBuffers(nrBuffers, &buf.front());
    m_vBuffers.insert(m_vBuffers.end(), buf.begin(), buf.end());
    return buf;
}

void GLManager::bindArrayBuffer(buffer_t buffer)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void GLManager::unbindArrayBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLManager::bindElementBuffer(buffer_t buffer)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
}

void GLManager::unbindElementBuffer()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

vertexArray_t GLManager::createVertexArray()
{
    vertexArray_t vao;
    glGenVertexArrays(1, &vao);
    m_vVertexArrays.push_back(vao);
    return vao;
}

std::vector<vertexArray_t> GLManager::createVertexArrays(size_t nrVertexArrays)
{
    std::vector<vertexArray_t> vaos;
    vaos.resize(nrVertexArrays);
    glGenVertexArrays(nrVertexArrays, &vaos.front());
    m_vVertexArrays.insert(m_vVertexArrays.end(), vaos.begin(), vaos.end());
    return vaos;
}

void GLManager::bindVertexArray(vertexArray_t vertexArray)
{
    glBindVertexArray(vertexArray);
}

void GLManager::unbindVertexArray()
{
    glBindVertexArray(0);
}

texture_t GLManager::createTexture(const std::string& ddsPath)
{
    ImageData data;
    bool success = openDdsImage(ddsPath, &data);
    if (success == false)
        return 0;

    // Create the texture
    texture_t textureID;
    glGenTextures(1, &textureID);
    m_vTextures.push_back(textureID);

    // Bind the newly created texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Fill the mipmaps
    unsigned int blockSize = (data.format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    for (unsigned int level = 0; level < data.mipMapCount && (data.width || data.height); ++level)
    {
        unsigned int size = ((data.width + 3) / 4) * ((data.height + 3) / 4) * blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, data.format, data.width, data.height, 0, size, data.buffer + offset);

        offset += size;
        data.width /= 2;
        data.height /= 2;
    }
    free(data.buffer);

    glBindTexture(GL_TEXTURE_2D, 0);
    return textureID;
}

void GLManager::bindTexture(texture_t texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);
}

void GLManager::unbindTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

texture_t GLManager::createSkyBox(const std::string& skyBoxFolderPath)
{
    const GLenum types[6] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };

    const std::string names[6] = {
        "posx.dds", "negx.dds",
        "posy.dds", "negy.dds",
        "posz.dds", "negz.dds"
    };

    std::string::const_iterator it = skyBoxFolderPath.end();
    --it;
    std::string baseDir = (*it == '/') ? skyBoxFolderPath : skyBoxFolderPath + "/";

    texture_t textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (size_t i = 0; i < 6; ++i)
    {
        std::string name = baseDir + names[i];
        ImageData data;
        bool success = openDdsImage(name, &data);
        if (success == false)
        {
            glDeleteTextures(1, &textureID);
            return 0;
        }
        // assert(data.mipMapCount == 1);

        unsigned int blockSize = (data.format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
        unsigned int size = ((data.width + 3) / 4) * ((data.height + 3) / 4) * blockSize;

        glCompressedTexImage2D(types[i], 0, data.format, data.width, data.height, 0, size, data.buffer);

        free(data.buffer);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    m_vTextures.push_back(textureID);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return textureID;
}

void GLManager::bindSkyBox(texture_t skyBox)
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyBox);
}

void GLManager::unbindSkyBox()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

GLManager& GLManager::getInstance()
{
    static GLManager manager;

    return manager;
}

bool GLManager::openDdsImage(const std::string& filename, ImageData* output)
{
    #define FOURCC_DXT1 0x31545844      // Equivalent to "DXT1" in ASCII
    #define FOURCC_DXT3 0x33545844      // Equivalent to "DXT3" in ASCII
    #define FOURCC_DXT5 0x35545844      // Equivalent to "DXT5" in ASCII

    // Try to open the file
    FILE* fp = fopen(filename.c_str(), "rb");
    if (fp == NULL)
        return false;

    // Verify the file type
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0)
    {
        fclose(fp);
        return false;
    }

    // Get the surface description
    unsigned char header[124];
    fread(&header, 124, 1, fp);

    output->height              = *(unsigned int*)&(header[ 8]);
    output->width               = *(unsigned int*)&(header[12]);
    unsigned int linearSize     = *(unsigned int*)&(header[16]);
    output->mipMapCount         = *(unsigned int*)&(header[24]);
    unsigned int fourCC         = *(unsigned int*)&(header[80]);

    unsigned int bufSize;

    // How big is it going to be including all mipmaps?
    bufSize = output->mipMapCount > 1 ? linearSize * 2 : linearSize;
    output->buffer = (unsigned char*)malloc(bufSize * sizeof(unsigned char));
    fread(output->buffer, 1, bufSize, fp);
    // Close the file pointer
    fclose(fp);

    // Deal with the 3 different formats, DXT1, DXT3 and DXT5
    // unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
    switch (fourCC)
    {
        case FOURCC_DXT1:
            output->format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            output->format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            output->format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            free(output->buffer);
            return false;
    }

    return true;
}
