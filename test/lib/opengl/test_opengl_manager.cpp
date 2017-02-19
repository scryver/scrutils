#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glmock.hpp"
#include "Scryver/OpenGL/Manager.hpp"
// #include "Scryver/Engine/Window.hpp"

using Scryver::OpenGL::GLManager;
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
    ASSERT_EQ(glewExperimental, GL_TRUE);

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

    uint32_t buf = manager.createBuffer();
    ASSERT_EQ(buf, 1u);

    EXPECT_CALL(GLMock, DeleteBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(0));

    manager.destroy();
}
