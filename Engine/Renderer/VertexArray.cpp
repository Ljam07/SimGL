#include "VertexArray.h"

#include "Renderer.h"

VertexArray::~VertexArray()
{
    // Destructor implementation
}

void VertexArray::Bind()
{
    // Bind the vertex array
    // Renderer::BindVertexArray(m_RendererID);
}

void VertexArray::Unbind()
{
    // Unbind the vertex array
    // Renderer::BindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    // Add a vertex buffer to the vertex array
    m_VertexBuffers.push_back(vertexBuffer);
    vertexBuffer->Bind();
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
    // Set the index buffer for the vertex array
    m_IndexBuffer = indexBuffer;
    indexBuffer->Bind();
}

std::shared_ptr<VertexArray> VertexArray::Create()
{
    // Create a new vertex array
    return std::make_shared<VertexArray>();
}