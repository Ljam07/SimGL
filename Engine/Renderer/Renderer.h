#pragma once
#include "Camera.h"
#include "Shader.h"
#include "VertexArray.h"

class Renderer
{
public:
    static void Init();

    static void OnWindowResize(uint32_t width, uint32_t height);

	// static void SetDimension(RendererAPI::Dimension dimension);
	// static void BeginScene(OrthographicCamera& camera);
	static void BeginScene(Camera& camera);
	static void EndScene();
  
	static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
};