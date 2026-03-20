#include "Renderer.h"

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));   //clear old window and in this case leave it black
}

void Renderer::Clear(const float clearColor[4]) const
{
    GLCall(glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
