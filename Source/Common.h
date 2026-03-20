#pragma once
#include <GL/glew.h>

//makros to help send an error message
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

constexpr float PI = 355.f / 113.f;
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
void Clamp(float& value, const float& minValue, const float& maxValue);
