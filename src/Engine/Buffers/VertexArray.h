#pragma once

#include "Engine/Buffers/VertexBuffer.h"
#include "Engine/Buffers/VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
private:

	unsigned int m_rendererID;
};

