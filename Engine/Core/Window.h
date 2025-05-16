#pragma once
#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  

struct WindowSpecs
{
    WindowSpecs(const std::string& title = "Application", uint32_t w = 800, uint32_t h = 600)
        : Title(title), Width(w), Height(h)
    {}

    uint32_t Width, Height;
    std::string Title;
};

class Window
{
public:
    ~Window();
    void CreateWindow(WindowSpecs specs = WindowSpecs());

    void DestroyWindow();
    
    void OnUpdate();
    bool ShouldWindowClose();

    void UpdateWindowDetails(WindowSpecs specs);

private:

    struct WindowDetails
    {
        uint32_t Width, Height;
        std::string Title;
    };

    WindowDetails m_WindowDetails;
    GLFWwindow* m_WindowHandle;
};