#include "glmock.hpp"


CGLMock::CGLMock()
    : GlewExperimental(GL_FALSE)
{
    // Empty
}

CGLMock::~CGLMock()
{
    // Empty
}

CGLMock& CGLMock::getInstance()
{
    static CGLMock instance;
    return instance;
}
