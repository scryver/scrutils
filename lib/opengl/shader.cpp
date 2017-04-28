#include "shader.hpp"

#include <cstdint>
#include <string>

#ifndef TESTING_ENABLED
#include <GL/glew.h>
#else
#include "../../test/lib/opengl/glmock.hpp"
#endif

#include "Scryver/Math/Matrix4.hpp"
#include "Scryver/Files/FileReader.hpp"
#include "Scryver/Debug/Expector.hpp"
#include "Scryver/Debug/Printer.hpp"

using Scryver::OpenGL::Shader;
using Scryver::OpenGL::uniform_t;

static GLuint createAndCompileShader(const std::string& source, GLenum shaderType);
#ifndef NDEBUG
static inline void printShaderError(GLuint shaderID, int infoLogLength);
static inline void printProgramError(GLuint programID, int infoLogLength);
#endif

Shader::Shader()
    : identifier(0)
{
    // Empty
}

Shader::~Shader()
{
    destroy();
}

bool Shader::initialize(const std::string& vertex, const std::string& fragment,
                        bool fromFiles)
{
    GLuint vertexShaderID;
    GLuint fragmentShaderID;

    if (fromFiles)
    {
        debugPrint("Creating vertex shader from file: " << vertex);
        std::string vertexCode;
        if (!Scryver::Files::readFile(vertex, vertexCode))
        {
            errorPrint("Impossible to open '" << vertex << "'. Are you in the right directory?");
            return false;
        }
        debugPrint("Creating fragment shader from file: " << fragment);
        std::string fragmentCode;
        if (!Scryver::Files::readFile(fragment, fragmentCode))
        {
            errorPrint("Impossible to open '" << fragment << "'. Are you in the right directory?");
            return false;
        }
        vertexShaderID = createAndCompileShader(vertexCode, GL_VERTEX_SHADER);
        if (vertexShaderID == 0)
        {
            errorPrint("Compiling vertex shader failed!");
            return false;
        }
        fragmentShaderID = createAndCompileShader(fragmentCode, GL_FRAGMENT_SHADER);
        if (fragmentShaderID == 0)
        {
            errorPrint("Compiling fragment shader failed!");
            glDeleteShader(vertexShaderID);
            return false;
        }
    }
    else
    {
        debugPrint("Creating vertex shader");
        vertexShaderID = createAndCompileShader(vertex, GL_VERTEX_SHADER);
        if (vertexShaderID == 0)
        {
            errorPrint("Compiling vertex shader failed!");
            return false;
        }
        debugPrint("Creating fragment shader");
        fragmentShaderID = createAndCompileShader(fragment, GL_FRAGMENT_SHADER);
        if (fragmentShaderID == 0)
        {
            errorPrint("Compiling fragment shader failed!");
            glDeleteShader(vertexShaderID);
            return false;
        }
    }

    debugPrint("Creating program");
    uint32_t id = glCreateProgram();
    glAttachShader(id, vertexShaderID);
    glAttachShader(id, fragmentShaderID);
    debugPrint("Linking program");
    glLinkProgram(id);

    glDetachShader(id, vertexShaderID);
    glDetachShader(id, fragmentShaderID);

    glDeleteShader(fragmentShaderID);
    glDeleteShader(vertexShaderID);

    GLint result = GL_FALSE;
    int infoLogLength;

    // Check the program
    glGetProgramiv(id, GL_LINK_STATUS, &result);
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (result == GL_FALSE)
    {
#ifndef NDEBUG
        if (infoLogLength > 0)
            printProgramError(id, infoLogLength);
#endif
        glDeleteProgram(id);
        identifier = shader_t::invalid();
        return false;
    }

    identifier = static_cast<shader_t>(id);

    return true;
}

void Shader::destroy()
{
    if (identifier != shader_t::invalid())
    {
        glDeleteProgram(static_cast<uint32_t>(identifier));
        identifier = shader_t::invalid();
    }
}

void Shader::use()
{
    makeSure(identifier != shader_t::invalid(), "Shader not initialized");
    glUseProgram(static_cast<uint32_t>(identifier));
}

uniform_t Shader::getUniform(const std::string& uniform)
{
    makeSure(identifier != shader_t::invalid(), "Shader not initialized");
    uniform_t location = static_cast<uniform_t>(
        glGetUniformLocation(static_cast<uint32_t>(identifier), uniform.c_str())
    );
    makeSure(location != uniform_t::invalid(), "Uniform does not exist");
    return location;
}

void Shader::uploadUniformOnce(const std::string& uniform, int value)
{
    uniform_t location = getUniform(uniform);
    uploadUniform(location, value);
}

void Shader::uploadUniform(uniform_t location, int value)
{
    makeSure(identifier != shader_t::invalid(), "Shader not initialized");
    glUniform1i(static_cast<uint32_t>(location), value);
}

void Shader::uploadUniform(uniform_t location, const Math::Matrix4f& value,
                           bool transpose)
{
    makeSure(identifier != shader_t::invalid(), "Shader not initialized");
    glUniformMatrix4fv(static_cast<uint32_t>(location), 1,
                       transpose ? GL_TRUE : GL_FALSE,
                       &value.m[0][0]);
}

GLuint createAndCompileShader(const std::string& source, GLenum shaderType)
{
    GLuint shaderID = glCreateShader(shaderType);

    GLint result = GL_FALSE;
    int infoLogLength;

    const char * sourcePointer = source.c_str();
    glShaderSource(shaderID, 1, &sourcePointer, NULL);
    debugPrint("Compiling shader");
    glCompileShader(shaderID);

    // Check shader
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (result == GL_FALSE)
    {
#ifndef NDEBUG
        if (infoLogLength > 0)
            printShaderError(shaderID, infoLogLength);
#endif
        glDeleteShader(shaderID);
        return 0;
    }

    return shaderID;
}

#ifndef NDEBUG
void printShaderError(GLuint shaderID, int infoLogLength)
{
    std::vector<char> shaderErrorMessage(infoLogLength+1);
    glGetShaderInfoLog(shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
    errorPrint(static_cast<const char*>(&shaderErrorMessage.front()));
}

void printProgramError(GLuint programID, int infoLogLength)
{
    std::vector<char> programErrorMessage(infoLogLength+1);
    glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
    errorPrint(static_cast<const char*>(&programErrorMessage.front()));
}
#endif
