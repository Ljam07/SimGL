#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

class RenderDispatcher
{
public:
    static void ClearColor(const glm::vec4& color);
    static void Clear();
    static void SetViewport(int x, int y, int width, int height);

    static void InitGlad();
};