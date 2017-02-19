#include <gtest/gtest.h>

#include "Scryver/OpenGL/Manager.hpp"
#include "Scryver/Engine/Window.hpp"

using Scryver::OpenGL::GLManager;
using Scryver::Engine::Window;


TEST(GLManager, Constructor)
{
    GLManager manager;
}

TEST(GLManager, InitializeWithoutContext)
{
    GLManager manager;

    ASSERT_FALSE(manager.initialize());
}

TEST(GLManager, InitializeWithContext)
{
    Window window;
    ASSERT_TRUE(window.initialize());

    GLManager manager;
    ASSERT_TRUE(manager.initialize());
}
