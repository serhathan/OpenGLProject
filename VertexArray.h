#pragma once
#include "VertexBuffer.h"
#include "BufferLayout.h"

class VertexArray
{
public:

	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vertexBuffer, const BufferLayout& layout);

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_RendererID;

};
