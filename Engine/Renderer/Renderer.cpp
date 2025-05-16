#include "Renderer.h"

void Renderer::Init()
{
    // Initialize the renderer API
    
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
    // Handle window resizing
    // RendererAPI::SetViewport(0, 0, width, height);
}

void Renderer::BeginScene(Camera& camera)
{
    // Begin the scene with the given camera
    // RendererAPI::SetCamera(camera);
}

void Renderer::EndScene()
{
    // End the scene
    // RendererAPI::EndScene();
}

void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
{
    // Submit the vertex array and shader for rendering
    // RendererAPI::Submit(shader, vertexArray, transform);
}