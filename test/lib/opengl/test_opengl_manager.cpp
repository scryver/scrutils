#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

#include "glmock.hpp"
#include "Scryver/OpenGL/Manager.hpp"
// #include "Scryver/Engine/Window.hpp"


using Scryver::OpenGL::GLManager;
using Scryver::OpenGL::Option;
using Scryver::OpenGL::buffer_t;
using Scryver::OpenGL::vertexArray_t;
// using Scryver::Engine::Window;


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
    ASSERT_EQ(1u, buf);

    EXPECT_CALL(GLMock, DeleteBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(0));

    manager.destroy();
}

TEST(GLManager, CreateMultipleBuffers)
{
    GLuint buffers[] = {1, 2, 3, 4, 5};
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, GenBuffers(5, testing::_))
        .Times(1)
        .WillOnce(testing::SetArrayArgument<1>(buffers, buffers + 5));

    std::vector<buffer_t> buf = manager.createBuffers(5);
    ASSERT_EQ(5u, buf.size());

    EXPECT_CALL(GLMock, DeleteBuffers(5, testing::_))
        .Times(1);

    manager.destroy();
}

TEST(GLManager, CreateSeperateBuffers)
{
    GLuint buffers[] = {4, 5, 6, 7};
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(3)
        .WillOnce(testing::SetArgPointee<1>(1))
        .WillOnce(testing::SetArgPointee<1>(2))
        .WillOnce(testing::SetArgPointee<1>(3));

    EXPECT_CALL(GLMock, GenBuffers(4, testing::_))
        .Times(1)
        .WillOnce(testing::SetArrayArgument<1>(buffers, buffers + 4));

    ASSERT_EQ(1u, manager.createBuffer());
    ASSERT_EQ(2u, manager.createBuffer());
    ASSERT_EQ(3u, manager.createBuffer());
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
    ASSERT_EQ(1u, buf);

    EXPECT_CALL(GLMock, DeleteVertexArrays(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(0));

    manager.destroy();
}

TEST(GLManager, CreateMultipleVertexArrays)
{
    GLuint buffers[] = {1, 2, 3, 4, 5};
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, GenVertexArrays(5, testing::_))
        .Times(1)
        .WillOnce(testing::SetArrayArgument<1>(buffers, buffers + 5));

    std::vector<vertexArray_t> buf = manager.createVertexArrays(5);
    ASSERT_EQ(5u, buf.size());

    EXPECT_CALL(GLMock, DeleteVertexArrays(5, testing::_))
        .Times(1);

    manager.destroy();
}

TEST(GLManager, CreateSeperateVertexArrays)
{
    GLuint buffers[] = {4, 5, 6, 7};
    GLManager& manager = GLManager::getInstance();

    EXPECT_CALL(GLMock, GenVertexArrays(1, testing::_))
        .Times(3)
        .WillOnce(testing::SetArgPointee<1>(1))
        .WillOnce(testing::SetArgPointee<1>(2))
        .WillOnce(testing::SetArgPointee<1>(3));

    EXPECT_CALL(GLMock, GenVertexArrays(4, testing::_))
        .Times(1)
        .WillOnce(testing::SetArrayArgument<1>(buffers, buffers + 4));

    ASSERT_EQ(1u, manager.createVertexArray());
    ASSERT_EQ(2u, manager.createVertexArray());
    ASSERT_EQ(3u, manager.createVertexArray());
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

    buffer_t buffer = manager.createVertexArray();
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

