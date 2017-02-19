#include <gtest/gtest.h>

#include "glmock.hpp"
#include "Scryver/OpenGL/Shader.hpp"

using Scryver::OpenGL::Shader;

const std::string brokenFile = "build/test/files/broken.glsl";
const std::string vertexFile = "build/test/files/vertex.glsl";
const std::string fragmentFile = "build/test/files/fragment.glsl";
const std::string linkErrorFile = "build/test/files/linker_error.glsl";


TEST(Shader, FailForNoPath)
{
    Shader s;

    ASSERT_FALSE(s.initialize("some", "thing", true));
    ASSERT_FALSE(s.initialize(vertexFile, "thing", true));
    ASSERT_FALSE(s.initialize("some", fragmentFile, true));
}

TEST(Shader, FailOnShaderFileCompilation)
{
    const char* shaderError = "Shader Error";
    EXPECT_CALL(GLMock, CreateShader(GL_VERTEX_SHADER))
        .Times(2)
        .WillOnce(testing::Return(1))
        .WillOnce(testing::Return(2));
    EXPECT_CALL(GLMock, CreateShader(GL_FRAGMENT_SHADER))
        .Times(1)
        .WillOnce(testing::Return(3));

    EXPECT_CALL(GLMock, ShaderSource(1, 1, testing::_, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, CompileShader(1)).Times(1);
    EXPECT_CALL(GLMock, GetShaderiv(1, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_FALSE));
    EXPECT_CALL(GLMock, GetShaderiv(1, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(12));
    EXPECT_CALL(GLMock, GetShaderInfoLog(1, 12, testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::SetArrayArgument<3>(shaderError, shaderError + 12));
    EXPECT_CALL(GLMock, DeleteShader(1)).Times(1);

    EXPECT_CALL(GLMock, ShaderSource(2, 1, testing::_, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, CompileShader(2)).Times(1);
    EXPECT_CALL(GLMock, GetShaderiv(2, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetShaderiv(2, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));
    EXPECT_CALL(GLMock, DeleteShader(2)).Times(1);

    EXPECT_CALL(GLMock, ShaderSource(3, 1, testing::_, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, CompileShader(3)).Times(1);
    EXPECT_CALL(GLMock, GetShaderiv(3, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_FALSE));
    EXPECT_CALL(GLMock, GetShaderiv(3, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));
    EXPECT_CALL(GLMock, DeleteShader(3)).Times(1);

    Shader s;

    ASSERT_FALSE(s.initialize(brokenFile, fragmentFile));
    ASSERT_FALSE(s.initialize(vertexFile, brokenFile));
}

TEST(Shader, CompileLinkSimpleShaderFiles)
{
    EXPECT_CALL(GLMock, CreateShader(GL_VERTEX_SHADER))
        .Times(1)
        .WillOnce(testing::Return(1));
    EXPECT_CALL(GLMock, ShaderSource(1, 1, testing::_, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, CompileShader(1)).Times(1);
    EXPECT_CALL(GLMock, GetShaderiv(1, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetShaderiv(1, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));

    EXPECT_CALL(GLMock, CreateShader(GL_FRAGMENT_SHADER))
        .Times(1)
        .WillOnce(testing::Return(2));
    EXPECT_CALL(GLMock, ShaderSource(2, 1, testing::_, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, CompileShader(2)).Times(1);
    EXPECT_CALL(GLMock, GetShaderiv(2, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetShaderiv(2, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));

    EXPECT_CALL(GLMock, CreateProgram()).Times(1).WillOnce(testing::Return(3));
    EXPECT_CALL(GLMock, AttachShader(3, 1)).Times(1);
    EXPECT_CALL(GLMock, AttachShader(3, 2)).Times(1);
    EXPECT_CALL(GLMock, LinkProgram(3));

    EXPECT_CALL(GLMock, DetachShader(3, 1)).Times(1);
    EXPECT_CALL(GLMock, DetachShader(3, 2)).Times(1);

    EXPECT_CALL(GLMock, DeleteShader(1)).Times(1);
    EXPECT_CALL(GLMock, DeleteShader(2)).Times(1);

    EXPECT_CALL(GLMock, GetProgramiv(3, GL_LINK_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetProgramiv(3, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));

    Shader s;

    ASSERT_TRUE(s.initialize(vertexFile, fragmentFile));

    // Ignore deletion check
    s.identifier = 0;
}

TEST(Shader, FailOnShaderFileLinking)
{
    EXPECT_CALL(GLMock, CreateShader(GL_VERTEX_SHADER))
        .Times(1)
        .WillOnce(testing::Return(1));
    EXPECT_CALL(GLMock, CreateShader(GL_FRAGMENT_SHADER))
        .Times(1)
        .WillOnce(testing::Return(2));

    EXPECT_CALL(GLMock, ShaderSource(1, 1, testing::_, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, ShaderSource(2, 1, testing::_, testing::_))
        .Times(1);

    EXPECT_CALL(GLMock, CompileShader(1)).Times(1);
    EXPECT_CALL(GLMock, CompileShader(2)).Times(1);

    EXPECT_CALL(GLMock, GetShaderiv(1, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetShaderiv(1, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));
    EXPECT_CALL(GLMock, GetShaderiv(2, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetShaderiv(2, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));

    EXPECT_CALL(GLMock, CreateProgram()).Times(1).WillOnce(testing::Return(3));
    EXPECT_CALL(GLMock, AttachShader(3, 1)).Times(1);
    EXPECT_CALL(GLMock, AttachShader(3, 2)).Times(1);
    EXPECT_CALL(GLMock, LinkProgram(3));

    EXPECT_CALL(GLMock, GetProgramiv(3, GL_LINK_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_FALSE));
    EXPECT_CALL(GLMock, GetProgramiv(3, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));

    EXPECT_CALL(GLMock, DetachShader(3, 1)).Times(1);
    EXPECT_CALL(GLMock, DetachShader(3, 2)).Times(1);

    EXPECT_CALL(GLMock, DeleteShader(1)).Times(1);
    EXPECT_CALL(GLMock, DeleteShader(2)).Times(1);

    EXPECT_CALL(GLMock, DeleteProgram(3)).Times(1);

    Shader s;

    ASSERT_FALSE(s.initialize(vertexFile, linkErrorFile));
}

TEST(Shader, FailOnShaderCompilation)
{
    EXPECT_CALL(GLMock, CreateShader(GL_VERTEX_SHADER))
        .Times(2)
        .WillOnce(testing::Return(1))
        .WillOnce(testing::Return(2));
    EXPECT_CALL(GLMock, CreateShader(GL_FRAGMENT_SHADER))
        .Times(1)
        .WillOnce(testing::Return(3));

    EXPECT_CALL(GLMock, ShaderSource(1, 1, testing::_, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, ShaderSource(2, 1, testing::_, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, ShaderSource(3, 1, testing::_, testing::_))
        .Times(1);

    EXPECT_CALL(GLMock, CompileShader(1)).Times(1);
    EXPECT_CALL(GLMock, CompileShader(2)).Times(1);
    EXPECT_CALL(GLMock, CompileShader(3)).Times(1);

    EXPECT_CALL(GLMock, GetShaderiv(1, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_FALSE));
    EXPECT_CALL(GLMock, GetShaderiv(1, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));
    EXPECT_CALL(GLMock, GetShaderiv(2, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetShaderiv(2, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));
    EXPECT_CALL(GLMock, GetShaderiv(3, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_FALSE));
    EXPECT_CALL(GLMock, GetShaderiv(3, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));

    EXPECT_CALL(GLMock, DeleteShader(1)).Times(1);
    EXPECT_CALL(GLMock, DeleteShader(2)).Times(1);
    EXPECT_CALL(GLMock, DeleteShader(3)).Times(1);

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
    EXPECT_CALL(GLMock, CreateShader(GL_VERTEX_SHADER))
        .Times(1)
        .WillOnce(testing::Return(1));
    EXPECT_CALL(GLMock, CreateShader(GL_FRAGMENT_SHADER))
        .Times(1)
        .WillOnce(testing::Return(2));

    EXPECT_CALL(GLMock, ShaderSource(1, 1, testing::_, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, ShaderSource(2, 1, testing::_, testing::_))
        .Times(1);

    EXPECT_CALL(GLMock, CompileShader(1)).Times(1);
    EXPECT_CALL(GLMock, CompileShader(2)).Times(1);

    EXPECT_CALL(GLMock, GetShaderiv(1, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetShaderiv(1, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));
    EXPECT_CALL(GLMock, GetShaderiv(2, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetShaderiv(2, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));

    EXPECT_CALL(GLMock, CreateProgram()).Times(1).WillOnce(testing::Return(3));
    EXPECT_CALL(GLMock, AttachShader(3, 1)).Times(1);
    EXPECT_CALL(GLMock, AttachShader(3, 2)).Times(1);
    EXPECT_CALL(GLMock, LinkProgram(3));

    EXPECT_CALL(GLMock, GetProgramiv(3, GL_LINK_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetProgramiv(3, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));

    EXPECT_CALL(GLMock, DetachShader(3, 1)).Times(1);
    EXPECT_CALL(GLMock, DetachShader(3, 2)).Times(1);

    EXPECT_CALL(GLMock, DeleteShader(1)).Times(1);
    EXPECT_CALL(GLMock, DeleteShader(2)).Times(1);

    EXPECT_CALL(GLMock, DeleteProgram(3)).Times(1);

    const char* simpleSrc = "#version 330 core\nvoid main() {}";

    Shader s;

    ASSERT_TRUE(s.initialize(simpleSrc, simpleSrc, false));
}

TEST(Shader, FailOnShaderLinking)
{
    const char* vertex = "#version 330 core\nlayout(location=0) in vec3 position;\nout vec3 colour;\nvoid main() { colour = vec3(1, 0, 0.4);}";
    const char* fragment = "#version 330 core\nin vec2 colour;\nout vec3 col;\nvoid main() { col = vec3(colour,0); }";
    const char* linkerError = "Linker Error";

    EXPECT_CALL(GLMock, CreateShader(GL_VERTEX_SHADER))
        .Times(1)
        .WillOnce(testing::Return(1));
    EXPECT_CALL(GLMock, CreateShader(GL_FRAGMENT_SHADER))
        .Times(1)
        .WillOnce(testing::Return(2));

    EXPECT_CALL(GLMock, ShaderSource(1, 1, testing::_, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, ShaderSource(2, 1, testing::_, testing::_))
        .Times(1);

    EXPECT_CALL(GLMock, CompileShader(1)).Times(1);
    EXPECT_CALL(GLMock, CompileShader(2)).Times(1);

    EXPECT_CALL(GLMock, GetShaderiv(1, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetShaderiv(1, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));
    EXPECT_CALL(GLMock, GetShaderiv(2, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetShaderiv(2, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));

    EXPECT_CALL(GLMock, CreateProgram()).Times(1).WillOnce(testing::Return(3));
    EXPECT_CALL(GLMock, AttachShader(3, 1)).Times(1);
    EXPECT_CALL(GLMock, AttachShader(3, 2)).Times(1);
    EXPECT_CALL(GLMock, LinkProgram(3));

    EXPECT_CALL(GLMock, GetProgramiv(3, GL_LINK_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_FALSE));
    EXPECT_CALL(GLMock, GetProgramiv(3, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(12));
    EXPECT_CALL(GLMock, GetProgramInfoLog(3, 12, testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::SetArrayArgument<3>(linkerError, linkerError + 12));

    EXPECT_CALL(GLMock, DetachShader(3, 1)).Times(1);
    EXPECT_CALL(GLMock, DetachShader(3, 2)).Times(1);

    EXPECT_CALL(GLMock, DeleteShader(1)).Times(1);
    EXPECT_CALL(GLMock, DeleteShader(2)).Times(1);

    EXPECT_CALL(GLMock, DeleteProgram(3)).Times(1);

    Shader s;

    ASSERT_FALSE(s.initialize(vertex, fragment, false));
}

TEST(Shader, UseSimpleShaderFiles)
{
    EXPECT_CALL(GLMock, CreateShader(GL_VERTEX_SHADER))
        .Times(1)
        .WillOnce(testing::Return(1));
    EXPECT_CALL(GLMock, ShaderSource(1, 1, testing::_, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, CompileShader(1)).Times(1);
    EXPECT_CALL(GLMock, GetShaderiv(1, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetShaderiv(1, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));

    EXPECT_CALL(GLMock, CreateShader(GL_FRAGMENT_SHADER))
        .Times(1)
        .WillOnce(testing::Return(2));
    EXPECT_CALL(GLMock, ShaderSource(2, 1, testing::_, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, CompileShader(2)).Times(1);
    EXPECT_CALL(GLMock, GetShaderiv(2, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetShaderiv(2, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));

    EXPECT_CALL(GLMock, CreateProgram()).Times(1).WillOnce(testing::Return(3));
    EXPECT_CALL(GLMock, AttachShader(3, 1)).Times(1);
    EXPECT_CALL(GLMock, AttachShader(3, 2)).Times(1);
    EXPECT_CALL(GLMock, LinkProgram(3));

    EXPECT_CALL(GLMock, DetachShader(3, 1)).Times(1);
    EXPECT_CALL(GLMock, DetachShader(3, 2)).Times(1);

    EXPECT_CALL(GLMock, DeleteShader(1)).Times(1);
    EXPECT_CALL(GLMock, DeleteShader(2)).Times(1);

    EXPECT_CALL(GLMock, GetProgramiv(3, GL_LINK_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetProgramiv(3, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));

    EXPECT_CALL(GLMock, UseProgram(3)).Times(1);
    Shader s;

    ASSERT_TRUE(s.initialize(vertexFile, fragmentFile));
    s.use();

    // Ignore deletion check
    s.identifier = 0;
}

TEST(Shader, GetUniformLocation)
{
    EXPECT_CALL(GLMock, CreateShader(GL_VERTEX_SHADER))
        .Times(1)
        .WillOnce(testing::Return(1));
    EXPECT_CALL(GLMock, ShaderSource(1, 1, testing::_, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, CompileShader(1)).Times(1);
    EXPECT_CALL(GLMock, GetShaderiv(1, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetShaderiv(1, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));

    EXPECT_CALL(GLMock, CreateShader(GL_FRAGMENT_SHADER))
        .Times(1)
        .WillOnce(testing::Return(2));
    EXPECT_CALL(GLMock, ShaderSource(2, 1, testing::_, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, CompileShader(2)).Times(1);
    EXPECT_CALL(GLMock, GetShaderiv(2, GL_COMPILE_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetShaderiv(2, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));

    EXPECT_CALL(GLMock, CreateProgram()).Times(1).WillOnce(testing::Return(3));
    EXPECT_CALL(GLMock, AttachShader(3, 1)).Times(1);
    EXPECT_CALL(GLMock, AttachShader(3, 2)).Times(1);
    EXPECT_CALL(GLMock, LinkProgram(3));

    EXPECT_CALL(GLMock, DetachShader(3, 1)).Times(1);
    EXPECT_CALL(GLMock, DetachShader(3, 2)).Times(1);

    EXPECT_CALL(GLMock, DeleteShader(1)).Times(1);
    EXPECT_CALL(GLMock, DeleteShader(2)).Times(1);

    EXPECT_CALL(GLMock, GetProgramiv(3, GL_LINK_STATUS, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(GL_TRUE));
    EXPECT_CALL(GLMock, GetProgramiv(3, GL_INFO_LOG_LENGTH, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<2>(0));

    const char* uniformName = "MyName";
    EXPECT_CALL(GLMock, GetUniformLocation(3, testing::StrEq(uniformName)))
        .Times(1)
        .WillOnce(testing::Return(5));
    Shader s;

    ASSERT_TRUE(s.initialize(vertexFile, fragmentFile));
    ASSERT_EQ(5u, s.getUniform(uniformName));

    // Ignore deletion check
    s.identifier = 0;
}
