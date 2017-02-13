#ifndef SCRYVER_TEST_OPEN_GL_MOCK_HPP
#define SCRYVER_TEST_OPEN_GL_MOCK_HPP

#include <gmock/gmock.h>

typedef unsigned int GLenum;
typedef size_t GLsizei;
typedef unsigned int GLuint;

const GLuint GL_ARRAY_BUFFER = 1;
const GLuint GL_ELEMENT_BUFFER = 2;

const GLuint GL_STATIC_DRAW = 1;
const GLuint GL_DYNAMIC_DRAW = 2;

const GLuint GL_FALSE = 0;
const GLuint GL_TRUE = 1;

const GLuint GL_BYTE = 0;
const GLuint GL_UNSIGNED_BYTE = 1;
const GLuint GL_SHORT = 2;
const GLuint GL_UNSIGNED_SHORT = 3;
const GLuint GL_INT = 4;
const GLuint GL_UNSIGNED_INT = 5;
const GLuint GL_FLOAT = 6;
const GLuint GL_DOUBLE = 7;
const GLuint GL_FIXED = 8;


class CGLMock {
public:
    /**
     * Buffers
     */
    MOCK_METHOD2( GenBuffers, void(GLsizei n, GLuint* buffers) );
    MOCK_METHOD2( DeleteBuffers, void(GLsizei n, GLuint* buffers) );
    MOCK_METHOD2( BindBuffer, void(GLuint t, GLuint buffer) );
    MOCK_METHOD4( BufferData, void(GLuint t, GLsizei size, const void* data, GLuint mode) );

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

    static CGLMock& GetInstance() {
        static CGLMock instance;

        return instance;
    }
};

#define GLMock  CGLMock::GetInstance()

#define glGenBuffers                GLMock.GenBuffers
#define glDeleteBuffers             GLMock.DeleteBuffers
#define glBindBuffer                GLMock.BindBuffer
#define glBufferData                GLMock.BufferData

#define glGenVertexArrays           GLMock.GenVertexArrays
#define glDeleteVertexArrays        GLMock.DeleteVertexArrays
#define glBindVertexArray           GLMock.BindVertexArray
#define glEnableVertexAttribArray   GLMock.EnableVertexAttribArray
#define glVertexAttribPointer       GLMock.VertexAttribPointer

#endif  // SCRYVER_TEST_OPEN_GL_MOCK_HPP
