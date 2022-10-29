#include "Renderer.h"
#include <glad/glad.h>

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES,ib.GetCount(),GL_UNSIGNED_INT,NULL);
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
