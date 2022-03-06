#pragma once
class VertexBuffer
{
public:

	VertexBuffer(const void* data, unsigned int size); // size = byte count, count = element count
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:

	unsigned int m_rendererID;

};

