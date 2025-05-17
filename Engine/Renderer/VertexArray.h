#pragma once

#include <stdint.h>
#include <memory>
#include <vector>

// forward declarations instead of including Buffer.h
class VertexBuffer;
class IndexBuffer;

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void Bind();
    void Unbind();

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
    
    const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
    const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
    static std::shared_ptr<VertexArray> Create();
private:
    uint32_t m_RendererID;

    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
};