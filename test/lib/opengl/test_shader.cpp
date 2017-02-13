#include <gtest/gtest.h>

#include <GL/glew.h>

#include "Scryver/OpenGL/Shader.hpp"
#include "Scryver/Engine/Window.hpp"

using Scryver::OpenGL::Shader;


TEST(Shader, FailForNoPath)
{
    Scryver::Engine::Window window;
    ASSERT_TRUE(window.initialize());

    Shader s;

    ASSERT_FALSE(s.initialize("some", "thing", true));
}
