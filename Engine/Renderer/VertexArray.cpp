#include "VertexArray.h"

#include "Buffer.h"

#include "Renderer.h"
#include <glad/glad.h>

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::Float:    return GL_FLOAT;
	case ShaderDataType::Float2:   return GL_FLOAT;
	case ShaderDataType::Float3:   return GL_FLOAT;
	case ShaderDataType::Float4:   return GL_FLOAT;
	case ShaderDataType::Mat3:     return GL_FLOAT;
	case ShaderDataType::Mat4:     return GL_FLOAT;
	case ShaderDataType::Int:      return GL_INT;
	case ShaderDataType::Int2:     return GL_INT;
	case ShaderDataType::Int3:     return GL_INT;
	case ShaderDataType::Int4:     return GL_INT;
	case ShaderDataType::Bool:     return GL_BOOL;
	}
}

VertexArray::VertexArray()
{
    // Constructor implementation
    glCreateVertexArrays(1, &m_RendererID);
}
VertexArray::~VertexArray()
{
    // Destructor implementation
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind()
{
    // Bind the vertex array
    // Renderer::BindVertexArray(m_RendererID);
	glBindVertexArray(m_RendererID);

}

void VertexArray::Unbind()
{
    // Unbind the vertex array
    // Renderer::BindVertexArray(0);
    glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    // Add a vertex buffer to the vertex array
    glBindVertexArray(m_RendererID);
	vertexBuffer->Bind();

	uint32_t index = 0;
	const auto& layout = vertexBuffer->GetLayout();
	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			element.GetComponentCount(),
			ShaderDataTypeToOpenGLBaseType(element.Type),
			element.Normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(const void*)element.Offset);
		index++;
	}

	m_VertexBuffers.push_back(vertexBuffer);
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
    glBindVertexArray(m_RendererID);
	indexBuffer->Bind();

	m_IndexBuffer = indexBuffer;
}

std::shared_ptr<VertexArray> VertexArray::Create()
{
    // Create a new vertex array
    return std::make_shared<VertexArray>();
}