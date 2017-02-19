#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glmock.hpp"
#include "Scryver/OpenGL/Buffer.hpp"


TEST(Buffer, Constructor)
{
    Scryver::OpenGL::Buffer b;

    ASSERT_EQ(b.identifier, 0u);
}

TEST(Buffer, Initializer)
{
    Scryver::OpenGL::Buffer b;

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));

    ASSERT_TRUE(b.initialize());
    ASSERT_NE(b.identifier, 0u);

    // Skip delete check
    b.identifier = 0;
}

TEST(Buffer, Destructor)
{
    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));
    EXPECT_CALL(GLMock, DeleteBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(0));

    {
        Scryver::OpenGL::Buffer b;

        ASSERT_TRUE(b.initialize());
        ASSERT_NE(b.identifier, 0u);
    }
}

TEST(Buffer, InitializeOnce)
{
    Scryver::OpenGL::Buffer b;

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));

    ASSERT_TRUE(b.initialize());
    ASSERT_FALSE(b.initialize());

    // Skip delete check
    b.identifier = 0;
}

TEST(Buffer, BufferData)
{
    Scryver::OpenGL::Buffer b;

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));

    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, BufferData(GL_ARRAY_BUFFER, sizeof(float) * 5, testing::_, GL_STATIC_DRAW))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 0))
        .Times(1);

    b.initialize();

    std::vector<float> data = {1, 2, 3, 4, 5};
    ASSERT_NE(b.bufferData<float>(data), 0u);

    // Skip delete check
    b.identifier = 0;
}

TEST(Buffer, BufferDataShouldFailWithoutInitialize)
{
    Scryver::OpenGL::Buffer b;

    ASSERT_EQ(b.bufferData<float>({1, 2, 3}), 0u);
}

TEST(Buffer, ShouldMapArrayType)
{
    Scryver::OpenGL::Buffer b;

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));

    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_BUFFER, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, BufferData(GL_ELEMENT_BUFFER, sizeof(float) * 5, testing::_, GL_STATIC_DRAW))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_BUFFER, 0))
        .Times(1);

    b.initialize();

    std::vector<float> data = {1, 2, 3, 4, 5};
    ASSERT_NE(b.bufferData<float>(data, Scryver::OpenGL::Buffer::ElementBuffer), 0u);

    // Skip delete check
    b.identifier = 0;
}

TEST(Buffer, OnlySupportsStaticAndDynamicDraw)
{
    Scryver::OpenGL::Buffer b;

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));

    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_BUFFER, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, BufferData(GL_ELEMENT_BUFFER, sizeof(float) * 5, testing::_, GL_STATIC_DRAW))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_BUFFER, 0))
        .Times(1);

    b.initialize();

    std::vector<float> data = {1, 2, 3, 4, 5};
    ASSERT_NE(b.bufferData<float>(data, Scryver::OpenGL::Buffer::ElementBuffer,
                                  Scryver::OpenGL::Buffer::Static), 0u);

    // Skip delete check
    b.identifier = 0;

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));

    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_BUFFER, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, BufferData(GL_ELEMENT_BUFFER, sizeof(float) * 5, testing::_, GL_DYNAMIC_DRAW))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_BUFFER, 0))
        .Times(1);

    b.initialize();

    ASSERT_NE(b.bufferData<float>(data, Scryver::OpenGL::Buffer::ElementBuffer,
                                  Scryver::OpenGL::Buffer::Dynamic), 0u);

    // Skip delete check
    b.identifier = 0;

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));

    b.initialize();

    ASSERT_EQ(b.bufferData<float>(data, Scryver::OpenGL::Buffer::ArrayBuffer,
                                  Scryver::OpenGL::Buffer::Stream), 0u);

    // Skip delete check
    b.identifier = 0;
}

TEST(Buffer, BufferDataWithTemplate)
{
    Scryver::OpenGL::Buffer b;

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));

    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, BufferData(GL_ARRAY_BUFFER, sizeof(unsigned char) * 2, testing::_, GL_STATIC_DRAW))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 0))
        .Times(1);

    b.initialize();

    std::vector<unsigned char> data = {125, 39};
    ASSERT_NE(b.bufferData<unsigned char>(data), 0u);

    // Skip delete check
    b.identifier = 0;
}

TEST(Buffer, PreInitTemplateBufferWithFloatData)
{
    Scryver::OpenGL::Buffer b;

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));

    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, BufferData(GL_ARRAY_BUFFER, sizeof(float) * 5, testing::_, GL_DYNAMIC_DRAW))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 0))
        .Times(1);

    b.initialize();

    std::vector<float> data = {1, 2, 3, 4, 5};
    ASSERT_NE(b.bufferFloatData(data, Scryver::OpenGL::Buffer::ArrayBuffer, Scryver::OpenGL::Buffer::Dynamic), 0u);

    // Skip delete check
    b.identifier = 0;
}

TEST(Buffer, InitializeWithDataDelegates)
{
    Scryver::OpenGL::Buffer b;

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));

    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, BufferData(GL_ARRAY_BUFFER, sizeof(float) * 5, testing::_, GL_STATIC_DRAW))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 0))
        .Times(1);


    std::vector<float> data = {1, 2, 3, 4, 5};
    unsigned int i = b.initialize(data);
    ASSERT_NE(i, 0u);
    ASSERT_EQ(i, b.identifier);

    // Skip delete check
    b.identifier = 0;
}

TEST(Buffer, BindKnowsType)
{
    Scryver::OpenGL::Buffer b;

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));

    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, BufferData(GL_ARRAY_BUFFER, sizeof(float) * 5, testing::_, GL_STATIC_DRAW))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 0))
        .Times(1);

    std::vector<float> data = {1, 2, 3, 4, 5};
    b.initialize(data);

    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, b.identifier))
        .Times(1);
    b.bind();

    // Skip delete check
    b.identifier = 0;
}

TEST(Buffer, UnbindMapsType)
{
    Scryver::OpenGL::Buffer b;
    const std::vector<unsigned char> data = {1, 2, 3, 4, 5};

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));

    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, BufferData(GL_ARRAY_BUFFER, sizeof(unsigned char) * 5, testing::_, GL_STATIC_DRAW))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 0))
        .Times(1);

    b.initialize(data, Scryver::OpenGL::Buffer::ArrayBuffer);

    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 0))
        .Times(1);

    b.unbind();

    // Skip delete check
    b.identifier = 0;

    EXPECT_CALL(GLMock, GenBuffers(1, testing::_))
        .Times(1)
        .WillOnce(testing::SetArgPointee<1>(1));

    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_BUFFER, testing::_))
        .Times(1);
    EXPECT_CALL(GLMock, BufferData(GL_ELEMENT_BUFFER, sizeof(unsigned char) * 5, testing::_, GL_STATIC_DRAW))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_BUFFER, 0))
        .Times(1);

    b.initialize(data, Scryver::OpenGL::Buffer::ElementBuffer);

    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_BUFFER, 0))
        .Times(1);

    b.unbind();

    // Skip delete check
    b.identifier = 0;


    EXPECT_CALL(GLMock, BindBuffer(GL_ARRAY_BUFFER, 0))
        .Times(1);
    EXPECT_CALL(GLMock, BindBuffer(GL_ELEMENT_BUFFER, 0))
        .Times(1);
    Scryver::OpenGL::Buffer::unbind(Scryver::OpenGL::Buffer::ArrayBuffer);
    Scryver::OpenGL::Buffer::unbind(Scryver::OpenGL::Buffer::ElementBuffer);
}
