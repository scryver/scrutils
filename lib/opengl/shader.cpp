#include "shader.hpp"

#include <cstdint>
#include <string>

#ifndef TESTING_ENABLED
#include <GL/glew.h>
#else
#include "../../test/lib/opengl/glmock.hpp"
#endif

#include "Scryver/Files/FileReader.hpp"
#include "Scryver/Debug/Printer.hpp"

using Scryver::OpenGL::Shader;

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
    identifier = glCreateProgram();
    glAttachShader(identifier, vertexShaderID);
    glAttachShader(identifier, fragmentShaderID);
    debugPrint("Linking program");
    glLinkProgram(identifier);

    glDetachShader(identifier, vertexShaderID);
    glDetachShader(identifier, fragmentShaderID);

    glDeleteShader(fragmentShaderID);
    glDeleteShader(vertexShaderID);

    GLint result = GL_FALSE;
    int infoLogLength;

    // Check the program
    glGetProgramiv(identifier, GL_LINK_STATUS, &result);
    glGetProgramiv(identifier, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (result == GL_FALSE)
    {
#ifndef NDEBUG
        if (infoLogLength > 0)
            printProgramError(identifier, infoLogLength);
#endif
        glDeleteProgram(identifier);
        identifier = 0;
        return false;
    }

    return true;
}

void Shader::destroy()
{
    if (identifier != 0)
    {
        glDeleteProgram(identifier);
        identifier = 0;
    }
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
