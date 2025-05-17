#include "Buffer.h"

#include <glad/glad.h>

std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
{
    return std::make_shared<VertexBuffer>(size);
}

std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
{
    return std::make_shared<VertexBuffer>(vertices, size);
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
	return std::make_shared<IndexBuffer>(indices, count);
}

VertexBuffer::VertexBuffer(uint32_t size)
{

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
{
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data, uint32_t size)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
    : m_Count(count)
{
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(uint32_t count)
    : m_Count(count)
{
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t IndexBuffer::GetCount()
{
    return m_Count;
}

