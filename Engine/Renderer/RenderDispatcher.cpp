#include "RenderDispatcher.h"

#include <iostream>

void RenderDispatcher::ClearColor(const glm::vec4& color)
{
    glClearColor(color.x, color.y, color.z, color.w);
}

void RenderDispatcher::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void RenderDispatcher::SetViewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

void RenderDispatcher::InitGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    } 
}