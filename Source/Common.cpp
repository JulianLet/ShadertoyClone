#include "Common.h"
#include <iostream>

//makros to help send an error message
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ", Line: " << line << std::endl;
        return false;
    }

    return true;
}

void Clamp(float& value, const float& minValue, const float& maxValue)
{
    value = std::max(minValue, std::min(value, maxValue));
}
