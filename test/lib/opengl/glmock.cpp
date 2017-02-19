#include "glmock.hpp"


CGLMock::CGLMock() {}
CGLMock::~CGLMock() {}

CGLMock& CGLMock::getInstance()
{
    static CGLMock instance;
    return instance;
}
