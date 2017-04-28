#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

#include "glmock.hpp"
#include "Scryver/OpenGL/Manager.hpp"
#include "Scryver/Math/Vector3D.hpp"
// #include "Scryver/Engine/Window.hpp"


using Scryver::OpenGL::GLManager;
using Scryver::OpenGL::Option;
using Scryver::OpenGL::DrawMethod;
using Scryver::OpenGL::buffer_t;
using Scryver::OpenGL::vertexArray_t;
// using Scryver::Engine::Window;
using Scryver::Math::Vector3Df;

struct Vertex
{
    Vector3Df position;
    float     alpha;

    Vertex(const Vector3Df& pos, float a)
        : position(pos)
        , alpha(a)
    {
        // Empty
    }
};


TEST(GLManager, Constructor)
{
    GLManager& manager = GLManager::getInstance();

    manager.destroy();
}

TEST(GLManager, InitializeWithoutContext)
{
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, GlewInit())
        .Times(1)
        .WillOnce(testing::Return(GL_FALSE));

    ASSERT_FALSE(manager.initialize());
    ASSERT_EQ(GL_TRUE, glewExperimental);

    manager.destroy();
}

TEST(GLManager, InitializeWithContext)
{
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, GlewInit())
        .Times(1)
        .WillOnce(testing::Return(GL_TRUE));

    ASSERT_TRUE(manager.initialize());

    manager.destroy();
}

TEST(GLManager, CreateBuffer)
{
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));

    buffer_t buf = manager.createBuffer();
    ASSERT_EQ(buffer_t(1), buf);

    EXPECT_CALL(GLMock, DeleteBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(0));

    manager.destroy();
}

TEST(GLManager, CreateMultipleBuffers)
{
    GLuint bufferIDs[] = {1, 2, 3, 4, 5};
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, GenBuffers(5, testing::_))
        .Times(1)
        .WillOnce(testing::SetArrayArgument<1>(bufferIDs, bufferIDs + 5));

    std::vector<buffer_t> buf = manager.createBuffers(5);
    ASSERT_EQ(5u, buf.size());

    EXPECT_CALL(GLMock, DeleteBuffers(5, testing::_))
        .Times(1);

    manager.destroy();
}

TEST(GLManager, CreateSeperateBuffers)
{
    GLuint bufferIDs[] = {4, 5, 6, 7};
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(3)
        .WillOnce(testing::SetArgPointee<1>(1))
        .WillOnce(testing::SetArgPointee<1>(2))
        .WillOnce(testing::SetArgPointee<1>(3));

    EXPECT_CALL(GLMock, GenBuffers(4, testing::_))
        .Times(1)
        .WillOnce(testing::SetArrayArgument<1>(bufferIDs, bufferIDs + 4));

    ASSERT_EQ(buffer_t(1), manager.createBuffer());
    ASSERT_EQ(buffer_t(2), manager.createBuffer());
    ASSERT_EQ(buffer_t(3), manager.createBuffer());
    std::vector<buffer_t> buf = manager.createBuffers(4);
    ASSERT_EQ(4u, buf.size());

    EXPECT_CALL(GLMock, DeleteBuffers(7, testing::_))
        .Times(1);

    manager.destroy();
}

TEST(GLManager, CreateVertexArray)
{
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, GenVertexArrays(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));

    vertexArray_t buf = manager.createVertexArray();
    ASSERT_EQ(vertexArray_t(1), buf);

    EXPECT_CALL(GLMock, DeleteVertexArrays(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(0));

    manager.destroy();
}

TEST(GLManager, CreateMultipleVertexArrays)
{
    GLuint buffers[] = {
        1, 2, 3, 4, 5
    };
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, GenVertexArrays(5, testing::_))
        .Times(1)
        .WillOnce(testing::SetArrayArgument<1>(buffers, buffers + 5));

    std::vector<vertexArray_t> buf = manager.createVertexArrays(5);
    ASSERT_EQ(5u, buf.size());
    ASSERT_EQ(vertexArray_t(1), buf.front());
    ASSERT_EQ(vertexArray_t(5), buf.back());

    EXPECT_CALL(GLMock, DeleteVertexArrays(5, testing::_))
        .Times(1);

    manager.destroy();
}

TEST(GLManager, CreateSeperateVertexArrays)
{
    GLuint buffers[] = {
        4, 5, 6, 7
    };
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, GenVertexArrays(1, testing::_))
        .Times(3)
        .WillOnce(testing::SetArgPointee<1>(1))
        .WillOnce(testing::SetArgPointee<1>(2))
        .WillOnce(testing::SetArgPointee<1>(3));

    EXPECT_CALL(GLMock, GenVertexArrays(4, testing::_))
        .Times(1)
        .WillOnce(testing::SetArrayArgument<1>(buffers, buffers + 4));

    ASSERT_EQ(vertexArray_t(1), manager.createVertexArray());
    ASSERT_EQ(vertexArray_t(2), manager.createVertexArray());
    ASSERT_EQ(vertexArray_t(3), manager.createVertexArray());
    std::vector<vertexArray_t> buf = manager.createVertexArrays(4);
    ASSERT_EQ(4u, buf.size());

    EXPECT_CALL(GLMock, DeleteVertexArrays(7, testing::_))
        .Times(1);

    manager.destroy();
}

TEST(GLManager, BindingArrayBuffer)
{
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));
    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 1u))
        .Times(1);
    EXPECT_CALL(GLMock, DeleteBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(0));

    buffer_t buffer = manager.createBuffer();
    manager.bindArrayBuffer(buffer);

    manager.destroy();
}

TEST(GLManager, UnbindingArrayBuffer)
{
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 0u))
        .Times(1);

    manager.unbindArrayBuffer();

    manager.destroy();
}

TEST(GLManager, BindingElementBuffer)
{
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(4));
    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 4u))
        .Times(1);
    EXPECT_CALL(GLMock, DeleteBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(0));

    buffer_t buffer = manager.createBuffer();
    manager.bindElementBuffer(buffer);

    manager.destroy();
}

TEST(GLManager, UnbindingElementBuffer)
{
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u))
        .Times(1);

    manager.unbindElementBuffer();

    manager.destroy();
}

TEST(GLManager, BindingVertexArray)
{
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, GenVertexArrays(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(3));
    EXPECT_CALL(GLMock, BindVertexArray(3u))
        .Times(1);
    EXPECT_CALL(GLMock, DeleteVertexArrays(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(0));

    vertexArray_t buffer = manager.createVertexArray();
    manager.bindVertexArray(buffer);

    manager.destroy();
}

TEST(GLManager, UnbindingVertexArray)
{
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, BindVertexArray(0u))
        .Times(1);

    manager.unbindVertexArray();

    manager.destroy();
}

TEST(GLManager, WireMode)
{
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, PolygonMode(GL_FRONT_AND_BACK, GL_LINE))
        .Times(2);
    EXPECT_CALL(GLMock, PolygonMode(GL_FRONT_AND_BACK, GL_FILL))
        .Times(1);

    EXPECT_FALSE(manager.wireMode());
    manager.wireMode(true);
    EXPECT_TRUE(manager.wireMode());
    manager.wireMode(false);
    EXPECT_FALSE(manager.wireMode());
    manager.wireMode(true);
    EXPECT_TRUE(manager.wireMode());
}

TEST(GLManager, ViewportChange)
{
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, Viewport(0, 0, 160, 240))
        .Times(1);
    EXPECT_CALL(GLMock, Viewport(0, 0, 320, 140))
        .Times(1);

    manager.viewport(160, 240);
    manager.viewport(320, 140);
}

TEST(GLManager, DepthTest)
{
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, Enable(GL_DEPTH_TEST))
        .Times(2);
    EXPECT_CALL(GLMock, Disable(GL_DEPTH_TEST))
        .Times(1);

    manager.enable(Option::DepthTest);
    manager.disable(Option::DepthTest);
    manager.enable(Option::DepthTest);
}

TEST(GLManager, ArrayBufferData)
{
    GLManager& manager = GLManager::getInstance();

    std::array<float, 7> arrayVertices = {
        1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f
    };
    std::vector<float> vectorVertices = {
        4.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f
    };
    Vector3Df vector3DVertices[] = {
        {1.0f, 6.0f, 3.0f}, {4.0f, 5.0f, 6.0f}
    };
    std::array<Vertex, 2> vertexVertices = {{
        {{1.0f, 2.0f, 3.0f}, 1.0f},
        {{2.0f, 6.0f, 6.0f}, 44.0f}
    }};

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .WillOnce(testing::SetArgPointee<1>(1))
        .WillOnce(testing::SetArgPointee<1>(2))
        .WillOnce(testing::SetArgPointee<1>(3))
        .WillOnce(testing::SetArgPointee<1>(4))
        .WillOnce(testing::SetArgPointee<1>(5))
        .WillOnce(testing::SetArgPointee<1>(6))
        .WillOnce(testing::SetArgPointee<1>(7))
        .WillOnce(testing::SetArgPointee<1>(8));
    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 1u))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 2u))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 3u))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 4u))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 5u))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 6u))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 7u))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 8u))
        .Times(1);
    EXPECT_CALL(GLMock, BufferData(GL_ARRAY_BUFFER, sizeof(float) * 7,
                                   arrayVertices.data(), GL_STATIC_DRAW))
        .Times(2);
    EXPECT_CALL(GLMock, BufferData(GL_ARRAY_BUFFER, sizeof(float) * 7,
                                   vectorVertices.data(), GL_DYNAMIC_DRAW))
        .Times(2);
    EXPECT_CALL(GLMock, BufferData(GL_ARRAY_BUFFER, sizeof(float) * 6,
                                   vector3DVertices, GL_STREAM_DRAW))
        .Times(2);
    EXPECT_CALL(GLMock, BufferData(GL_ARRAY_BUFFER, sizeof(float) * 8,
                                   vertexVertices.data(), GL_STATIC_DRAW))
        .Times(2);
    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 0))
        .Times(8);
    EXPECT_CALL(GLMock, DeleteBuffers(8, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(0));

    buffer_t buffer1 = manager.createBuffer();
    buffer_t buffer2 = manager.createBuffer();
    buffer_t buffer3 = manager.createBuffer();
    buffer_t buffer4 = manager.createBuffer();
    manager.bufferArrayData(buffer1, arrayVertices);
    manager.bufferArrayData(buffer2, vectorVertices, DrawMethod::DynamicDraw);
    manager.bufferArrayData(buffer3, vector3DVertices, sizeof(vector3DVertices), DrawMethod::StreamDraw);
    manager.bufferArrayData(buffer4, vertexVertices, DrawMethod::StaticDraw);

    manager.createArrayBuffer(arrayVertices);
    manager.createArrayBuffer(vectorVertices, DrawMethod::DynamicDraw);
    manager.createArrayBuffer(vector3DVertices, sizeof(vector3DVertices), DrawMethod::StreamDraw);
    manager.createArrayBuffer(vertexVertices, DrawMethod::StaticDraw);

    manager.destroy();
}

TEST(GLManager, ElementBufferData)
{
    GLManager& manager = GLManager::getInstance();

    std::array<uint32_t, 7> arrayIndices = {
        1, 2, 3, 4, 5, 6, 7
    };
    std::vector<uint16_t> vectorIndices = {
        4, 2, 3, 4, 5, 6, 7
    };
    uint8_t cStyleIndices[] = {
        1, 6, 3, 4, 5, 6
    };
    std::array<uint16_t, 8> otherArrayIndices = {
        1, 2, 3, 1,
        2, 6, 6, 44
    };

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .WillOnce(testing::SetArgPointee<1>(1))
        .WillOnce(testing::SetArgPointee<1>(2))
        .WillOnce(testing::SetArgPointee<1>(3))
        .WillOnce(testing::SetArgPointee<1>(4))
        .WillOnce(testing::SetArgPointee<1>(5))
        .WillOnce(testing::SetArgPointee<1>(6))
        .WillOnce(testing::SetArgPointee<1>(7))
        .WillOnce(testing::SetArgPointee<1>(8));
    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 1u))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 2u))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 3u))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 4u))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 5u))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 6u))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 7u))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 8u))
        .Times(1);
    EXPECT_CALL(GLMock, BufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 7,
                                   arrayIndices.data(), GL_STATIC_DRAW))
        .Times(2);
    EXPECT_CALL(GLMock, BufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 7,
                                   vectorIndices.data(), GL_DYNAMIC_DRAW))
        .Times(2);
    EXPECT_CALL(GLMock, BufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint8_t) * 6,
                                   cStyleIndices, GL_STREAM_DRAW))
        .Times(2);
    EXPECT_CALL(GLMock, BufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 8,
                                   otherArrayIndices.data(), GL_STATIC_DRAW))
        .Times(2);
    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))
        .Times(8);
    EXPECT_CALL(GLMock, DeleteBuffers(8, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(0));

    buffer_t buffer1 = manager.createBuffer();
    buffer_t buffer2 = manager.createBuffer();
    buffer_t buffer3 = manager.createBuffer();
    buffer_t buffer4 = manager.createBuffer();
    manager.bufferElementData(buffer1, arrayIndices);
    manager.bufferElementData(buffer2, vectorIndices, DrawMethod::DynamicDraw);
    manager.bufferElementData(buffer3, cStyleIndices, sizeof(cStyleIndices), DrawMethod::StreamDraw);
    manager.bufferElementData(buffer4, otherArrayIndices, DrawMethod::StaticDraw);

    manager.createElementBuffer(arrayIndices);
    manager.createElementBuffer(vectorIndices, DrawMethod::DynamicDraw);
    manager.createElementBuffer(cStyleIndices, sizeof(cStyleIndices), DrawMethod::StreamDraw);
    manager.createElementBuffer(otherArrayIndices, DrawMethod::StaticDraw);

    manager.destroy();
}

TEST(GLManager, VertexAttributes)
{
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, GenVertexArrays(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));
    EXPECT_CALL(GLMock, BindVertexArray(1u))
        .Times(1);
    EXPECT_CALL(GLMock, EnableVertexAttribArray(0u))
        .Times(1);
    EXPECT_CALL(GLMock, EnableVertexAttribArray(1u))
        .Times(1);
    EXPECT_CALL(GLMock, VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                            sizeof(float) * 4,
                                            reinterpret_cast<void*>(0)))
        .Times(1);
    EXPECT_CALL(GLMock, VertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE,
                                            sizeof(float) * 4,
                                            reinterpret_cast<void*>(3 * 4)))
        .Times(1);
    EXPECT_CALL(GLMock, DisableVertexAttribArray(1u))
        .Times(1);
    EXPECT_CALL(GLMock, DisableVertexAttribArray(0u))
        .Times(1);
    EXPECT_CALL(GLMock, BindVertexArray(0u))
        .Times(1);
    EXPECT_CALL(GLMock, DeleteVertexArrays(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(0));

    vertexArray_t vertexAttribs = manager.createVertexArray();
    manager.bindVertexArray(vertexAttribs);
    manager.enableVertexAttribute(0);
    manager.enableVertexAttribute(1);
    manager.vertexAttributes(0, 3, sizeof(Vertex), offsetof(Vertex, position));
    manager.vertexAttributes(1, 1, sizeof(Vertex), offsetof(Vertex, alpha));
    manager.disableVertexAttribute(1);
    manager.disableVertexAttribute(0);
    manager.unbindVertexArray();

    manager.destroy();
}
