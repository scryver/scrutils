#ifndef SCRYVER_TEST_OPEN_GL_MOCK_HPP
#define SCRYVER_TEST_OPEN_GL_MOCK_HPP

#include <gmock/gmock.h>

typedef char GLchar;
typedef unsigned int GLenum;
typedef size_t GLsizei;
typedef unsigned int GLuint;
typedef int GLint;
typedef void GLvoid;
typedef float GLfloat;

const GLenum GL_ARRAY_BUFFER = 0;
const GLenum GL_ELEMENT_ARRAY_BUFFER = 1;

const GLenum GL_STATIC_DRAW = 2;
const GLenum GL_DYNAMIC_DRAW = 3;
const GLenum GL_STREAM_DRAW = 33;

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

const GLenum GL_TEXTURE_2D = 50;
const GLenum GL_TEXTURE_CUBE_MAP = 51;
const GLenum GL_TEXTURE_CUBE_MAP_POSITIVE_X = 52;
const GLenum GL_TEXTURE_CUBE_MAP_NEGATIVE_X = 53;
const GLenum GL_TEXTURE_CUBE_MAP_POSITIVE_Y = 54;
const GLenum GL_TEXTURE_CUBE_MAP_NEGATIVE_Y = 55;
const GLenum GL_TEXTURE_CUBE_MAP_POSITIVE_Z = 56;
const GLenum GL_TEXTURE_CUBE_MAP_NEGATIVE_Z = 57;

const GLenum GL_TEXTURE0 = 60;
const GLenum GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS = 61;


const GLenum GL_TEXTURE_MAG_FILTER = 70;
const GLenum GL_TEXTURE_MIN_FILTER = 71;
const GLenum GL_TEXTURE_WRAP_S = 72;
const GLenum GL_TEXTURE_WRAP_T = 73;
const GLenum GL_TEXTURE_WRAP_R = 74;

const GLint  GL_LINEAR = 75;
const GLint  GL_CLAMP_TO_EDGE = 76;

const GLenum GL_COMPRESSED_RGBA_S3TC_DXT1_EXT = 180;
const GLenum GL_COMPRESSED_RGBA_S3TC_DXT3_EXT = 181;
const GLenum GL_COMPRESSED_RGBA_S3TC_DXT5_EXT = 182;

const GLenum GL_DEPTH_TEST = 200;

const GLenum GL_FRONT = 251;
const GLenum GL_BACK = 252;
const GLenum GL_FRONT_AND_BACK = 253;

const GLenum GL_LINE = 300;
const GLenum GL_FILL = 301;

const GLenum GL_TRIANGLES = 350;

class CGLMock {
public:
    CGLMock();
    virtual ~CGLMock();

    /**
     * GLEW
     */
    GLuint GlewExperimental;
    MOCK_METHOD0( GlewInit,                 GLuint() );

    /**
     * Generic
     */
    MOCK_METHOD1( Enable,                   void(GLenum mode) );
    MOCK_METHOD1( Disable,                  void(GLenum mode) );
    MOCK_METHOD1( Clear,                    void(GLenum flags) );
    MOCK_METHOD2( PolygonMode,              void(GLenum face, GLenum mode));
    MOCK_METHOD4( Viewport,                 void(GLint x, GLint y, GLsizei width, GLsizei height));

    /**
     * Buffers
     */
    MOCK_METHOD2( GenBuffers,               void(GLsizei n, GLuint* buffers) );
    MOCK_METHOD2( DeleteBuffers,            void(GLsizei n, GLuint* buffers) );
    MOCK_METHOD2( BindBuffer,               void(GLenum t, GLuint buffer) );
    MOCK_METHOD4( BufferData,               void(GLenum t, GLsizei size, const void* data, GLenum mode) );

    /**
     * Vertex Attributes
     */
    MOCK_METHOD2( GenVertexArrays,          void(GLsizei n, GLuint* vertexArrays) );
    MOCK_METHOD2( DeleteVertexArrays,       void(GLsizei n, GLuint* vertexArrays) );
    MOCK_METHOD1( BindVertexArray,          void(GLuint vertexArrays) );
    MOCK_METHOD1( EnableVertexAttribArray,  void(GLuint attribute) );
    MOCK_METHOD1( DisableVertexAttribArray, void(GLuint attribute) );
    MOCK_METHOD6( VertexAttribPointer,      void(GLuint attribute, GLsizei size,
                                                 GLenum type, GLenum normal,
                                                 GLsizei stride, void* offset) );

    /**
     * Drawing methods
     */
    MOCK_METHOD4( DrawElements,             void(GLenum mode, GLsizei count, GLenum type,
                                                 const GLvoid* indices) );

    /**
     * Shaders
     */
    MOCK_METHOD1( CreateShader,             GLuint(GLenum type) );
    MOCK_METHOD4( ShaderSource,             void(GLuint shader, GLsizei nr, const GLchar** source, const GLint* length) );
    MOCK_METHOD1( CompileShader,            void(GLuint shader) );
    MOCK_METHOD3( GetShaderiv,              void(GLuint shader, GLenum status, GLint* result) );
    MOCK_METHOD4( GetShaderInfoLog,         void(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) );
    MOCK_METHOD1( DeleteShader,             void(GLuint shader) );

    MOCK_METHOD0( CreateProgram,            GLuint() );
    MOCK_METHOD2( AttachShader,             void(GLuint program, GLuint shader) );
    MOCK_METHOD2( DetachShader,             void(GLuint program, GLuint shader) );
    MOCK_METHOD1( LinkProgram,              void(GLuint program) );
    MOCK_METHOD3( GetProgramiv,             void(GLuint program, GLenum status, GLint* result) );
    MOCK_METHOD4( GetProgramInfoLog,        void(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) );
    MOCK_METHOD1( DeleteProgram,            void(GLuint program) );
    MOCK_METHOD1( UseProgram,               void(GLuint program) );

    MOCK_METHOD2( GetUniformLocation,       GLuint(GLuint program, const GLchar* name) );
    MOCK_METHOD2( Uniform1i,                void(GLint location, GLint value) );
    MOCK_METHOD4( UniformMatrix4fv,         void(GLint location, GLsizei count,
                                                 GLenum transpose, const GLfloat* value) );

    /**
     * Textures
     */
    MOCK_METHOD2( GenTextures,              void(GLsizei n, GLuint* textures) );
    MOCK_METHOD2( DeleteTextures,           void(GLsizei n, GLuint* textures) );
    MOCK_METHOD2( BindTexture,              void(GLenum t, GLuint texure) );
    MOCK_METHOD3( TexParameteri,            void(GLenum t, GLenum name, GLint param) );
    MOCK_METHOD8( CompressedTexImage2D,     void(GLenum t, GLint level, GLenum internalFmt,
                                                 GLsizei width, GLsizei height, GLint border,
                                                 GLsizei imageSize, const GLvoid* data) );
    MOCK_METHOD1( ActiveTexture,            void(GLenum texture) );


    static CGLMock& getInstance();
};

#define GLMock                      CGLMock::getInstance()

#define glewExperimental            GLMock.GlewExperimental
#define glewInit                    GLMock.GlewInit

#define glEnable                    GLMock.Enable
#define glDisable                   GLMock.Disable
#define glClear                     GLMock.Clear
#define glPolygonMode               GLMock.PolygonMode
#define glViewport                  GLMock.Viewport

#define glGenBuffers                GLMock.GenBuffers
#define glDeleteBuffers             GLMock.DeleteBuffers
#define glBindBuffer                GLMock.BindBuffer
#define glBufferData                GLMock.BufferData

#define glGenVertexArrays           GLMock.GenVertexArrays
#define glDeleteVertexArrays        GLMock.DeleteVertexArrays
#define glBindVertexArray           GLMock.BindVertexArray
#define glEnableVertexAttribArray   GLMock.EnableVertexAttribArray
#define glDisableVertexAttribArray  GLMock.DisableVertexAttribArray
#define glVertexAttribPointer       GLMock.VertexAttribPointer

#define glDrawElements              GLMock.DrawElements

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
#define glUseProgram                GLMock.UseProgram
#define glGetUniformLocation        GLMock.GetUniformLocation
#define glUniform1i                 GLMock.Uniform1i
#define glUniformMatrix4fv          GLMock.UniformMatrix4fv

#define glGenTextures               GLMock.GenTextures
#define glDeleteTextures            GLMock.DeleteTextures
#define glBindTexture               GLMock.BindTexture
#define glTexParameteri             GLMock.TexParameteri
#define glCompressedTexImage2D      GLMock.CompressedTexImage2D
#define glActiveTexture             GLMock.ActiveTexture

#endif  // SCRYVER_TEST_OPEN_GL_MOCK_HPP
