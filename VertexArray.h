#pragma once
#include "VertexBuffer.h"

class BufferLayout;


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
