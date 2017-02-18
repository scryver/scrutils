#include <gtest/gtest.h>

#include <GL/glew.h>

#include "Scryver/OpenGL/Shader.hpp"
#include "Scryver/Engine/Window.hpp"

using Scryver::OpenGL::Shader;

const std::string brokenFile = "build/test/files/broken.glsl";
const std::string vertexFile = "build/test/files/vertex.glsl";
const std::string fragmentFile = "build/test/files/fragment.glsl";
const std::string linkErrorFile = "build/test/files/linker_error.glsl";


TEST(Shader, FailForNoPath)
{
    Scryver::Engine::Window window;
    ASSERT_TRUE(window.initialize());

    Shader s;

    ASSERT_FALSE(s.initialize("some", "thing", true));
    ASSERT_FALSE(s.initialize(vertexFile, "thing", true));
    ASSERT_FALSE(s.initialize("some", fragmentFile, true));
}

TEST(Shader, FailOnShaderFileCompilation)
{
    Scryver::Engine::Window window;
    ASSERT_TRUE(window.initialize());

    Shader s;

    ASSERT_FALSE(s.initialize(brokenFile, fragmentFile));
    ASSERT_FALSE(s.initialize(vertexFile, brokenFile));
}

TEST(Shader, CompileLinkSimpleShaderFiles)
{
    Scryver::Engine::Window window;
    ASSERT_TRUE(window.initialize());

    Shader s;

    ASSERT_TRUE(s.initialize(vertexFile, fragmentFile));
}

TEST(Shader, FailOnShaderFileLinking)
{
    Scryver::Engine::Window window;
    ASSERT_TRUE(window.initialize());

    Shader s;

    ASSERT_FALSE(s.initialize(vertexFile, linkErrorFile));
}

TEST(Shader, FailOnShaderCompilation)
{
    Scryver::Engine::Window window;
    ASSERT_TRUE(window.initialize());

    Shader s;

    ASSERT_FALSE(s.initialize("vec2 outC;\nmain(){}", "main(){}", false));
    ASSERT_FALSE(s.initialize(
"#version 330 core\n"
"layout(location=0) in vec3 position;\n"
"void main() {\n"
"   gl_Position = vec4(position, 1.0);\n"
"}", "void main(){ colour = vec4(); }", false));
}

TEST(Shader, CompileLinkSimpleShader)
{
    const char* simpleSrc = "#version 330 core\nvoid main() {}";

    Scryver::Engine::Window window;
    ASSERT_TRUE(window.initialize());

    Shader s;

    ASSERT_TRUE(s.initialize(simpleSrc, simpleSrc, false));
}

TEST(Shader, FailOnShaderLinking)
{
    const char* vertex = "#version 330 core\nlayout(location=0) in vec3 position;\nout vec3 colour;\nvoid main() { colour = vec3(1, 0, 0.4);}";
    const char* fragment = "#version 330 core\nin vec2 colour;\nout vec3 col;\nvoid main() { col = vec3(colour,0); }";

    Scryver::Engine::Window window;
    ASSERT_TRUE(window.initialize());

    Shader s;

    ASSERT_FALSE(s.initialize(vertex, fragment, false));
}
