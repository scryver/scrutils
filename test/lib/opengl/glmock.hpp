#ifndef SCRYVER_TEST_OPEN_GL_MOCK_HPP
#define SCRYVER_TEST_OPEN_GL_MOCK_HPP

#include <gmock/gmock.h>

typedef char GLchar;
typedef unsigned int GLenum;
typedef size_t GLsizei;
typedef unsigned int GLuint;
typedef int GLint;

const GLenum GL_ARRAY_BUFFER = 0;
const GLenum GL_ELEMENT_BUFFER = 1;

const GLenum GL_STATIC_DRAW = 2;
const GLenum GL_DYNAMIC_DRAW = 3;

const GLenum GL_FALSE = 4;
const GLenum GL_TRUE = 5;
const GLuint GLEW_OK = GL_TRUE;

const GLenum GL_BYTE = 6;
const GLenum GL_UNSIGNED_BYTE = 7;
const GLenum GL_SHORT = 8;
const GLenum GL_UNSIGNED_SHORT = 9;
const GLenum GL_INT = 10;
const GLenum GL_UNSIGNED_INT = 11;
const GLenum GL_FLOAT = 12;
const GLenum GL_DOUBLE = 13;
const GLenum GL_FIXED = 14;

const GLenum GL_VERTEX_SHADER = 15;
const GLenum GL_FRAGMENT_SHADER = 16;

const GLenum GL_COMPILE_STATUS = 17;
const GLenum GL_LINK_STATUS = 18;

const GLenum GL_INFO_LOG_LENGTH = 19;

class CGLMock {
public:
    CGLMock();
    virtual ~CGLMock();

    /**
     * GLEW
     */
    GLuint GlewExperimental;
    MOCK_METHOD0( GlewInit, GLuint() );

    /**
     * Generic
     */
    MOCK_METHOD1( Enable, void(GLenum mode) );
    MOCK_METHOD1( Clear,  void(GLenum flags) );

    /**
     * Buffers
     */
    MOCK_METHOD2( GenBuffers, void(GLsizei n, GLuint* buffers) );
    MOCK_METHOD2( DeleteBuffers, void(GLsizei n, GLuint* buffers) );
    MOCK_METHOD2( BindBuffer, void(GLenum t, GLuint buffer) );
    MOCK_METHOD4( BufferData, void(GLenum t, GLsizei size, const void* data, GLenum mode) );

    /**
     * Vertex Attributes
     */
    MOCK_METHOD2( GenVertexArrays, void(GLsizei n, GLuint* vertexArrays) );
    MOCK_METHOD2( DeleteVertexArrays, void(GLsizei n, GLuint* vertexArrays) );
    MOCK_METHOD1( BindVertexArray, void(GLuint vertexArrays) );
    MOCK_METHOD1( EnableVertexAttribArray, void(GLuint attribute) );
    MOCK_METHOD6( VertexAttribPointer, void(GLuint attribute,
                                            GLsizei size,
                                            GLenum type,
                                            GLenum normal,
                                            GLsizei stride,
                                            void* offset) );

    /**
     * Shaders
     */
    MOCK_METHOD1( CreateShader, GLuint(GLenum type) );
    MOCK_METHOD4( ShaderSource, void(GLuint shader, GLsizei nr, const GLchar** source, const GLint* length) );
    MOCK_METHOD1( CompileShader, void(GLuint shader) );
    MOCK_METHOD3( GetShaderiv, void(GLuint shader, GLenum status, GLint* result) );
    MOCK_METHOD4( GetShaderInfoLog, void(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) );
    MOCK_METHOD1( DeleteShader, void(GLuint shader) );

    MOCK_METHOD0( CreateProgram, GLuint() );
    MOCK_METHOD2( AttachShader, void(GLuint program, GLuint shader) );
    MOCK_METHOD2( DetachShader, void(GLuint program, GLuint shader) );
    MOCK_METHOD1( LinkProgram, void(GLuint program) );
    MOCK_METHOD3( GetProgramiv, void(GLuint program, GLenum status, GLint* result) );
    MOCK_METHOD4( GetProgramInfoLog, void(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) );
    MOCK_METHOD1( DeleteProgram, void(GLuint program) );

    static CGLMock& getInstance();
};

#define GLMock  CGLMock::getInstance()

#define glewExperimental            GLMock.GlewExperimental
#define glewInit                    GLMock.GlewInit

#define glEnable                    GLMock.Enable
#define glClear                     GLMock.Clear

#define glGenBuffers                GLMock.GenBuffers
#define glDeleteBuffers             GLMock.DeleteBuffers
#define glBindBuffer                GLMock.BindBuffer
#define glBufferData                GLMock.BufferData

#define glGenVertexArrays           GLMock.GenVertexArrays
#define glDeleteVertexArrays        GLMock.DeleteVertexArrays
#define glBindVertexArray           GLMock.BindVertexArray
#define glEnableVertexAttribArray   GLMock.EnableVertexAttribArray
#define glVertexAttribPointer       GLMock.VertexAttribPointer

#define glCreateShader              GLMock.CreateShader
#define glShaderSource              GLMock.ShaderSource
#define glCompileShader             GLMock.CompileShader
#define glGetShaderiv               GLMock.GetShaderiv
#define glGetShaderInfoLog          GLMock.GetShaderInfoLog
#define glDeleteShader              GLMock.DeleteShader
#define glCreateProgram             GLMock.CreateProgram
#define glAttachShader              GLMock.AttachShader
#define glDetachShader              GLMock.DetachShader
#define glLinkProgram               GLMock.LinkProgram
#define glGetProgramiv              GLMock.GetProgramiv
#define glGetProgramInfoLog         GLMock.GetProgramInfoLog
#define glDeleteProgram             GLMock.DeleteProgram

#endif  // SCRYVER_TEST_OPEN_GL_MOCK_HPP
