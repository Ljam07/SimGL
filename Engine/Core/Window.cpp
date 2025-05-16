#include "Window.h"
#include "../Renderer/RenderDispatcher.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void Window::CreateWindow(WindowSpecs specs)
{
    m_WindowDetails.Title = specs.Title;
    m_WindowDetails.Width = specs.Width;
    m_WindowDetails.Height = specs.Height;

    if (!glfwInit())
    {
        std::cout << "Could not init GLFW!\n";
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,    GLFW_OPENGL_CORE_PROFILE);
    

    m_WindowHandle = glfwCreateWindow(m_WindowDetails.Width, m_WindowDetails.Height, m_WindowDetails.Title.c_str(), NULL, NULL);

    if (!m_WindowHandle)
    {
        glfwTerminate();
        std::cout << "Could not create window!\n";
        exit(-1);
    }

    glfwMakeContextCurrent(m_WindowHandle);

    RenderDispatcher::InitGlad();

    RenderDispatcher::SetViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(m_WindowHandle, framebuffer_size_callback);  

}


void Window::OnUpdate()
{
    /* Render here */
    RenderDispatcher::ClearColor({0.2f, 0.3f, 0.3f, 1.0f});
    RenderDispatcher::Clear();

    /* Swap front and back buffers */
    glfwSwapBuffers(m_WindowHandle);

    /* Poll for and process events */
    glfwPollEvents();
}

bool Window::ShouldWindowClose()
{
    return glfwWindowShouldClose(m_WindowHandle);
}

void Window::DestroyWindow()
{
    glfwTerminate();
}

Window::~Window()
{
    DestroyWindow();
}

void Window::UpdateWindowDetails(WindowSpecs specs)
{
    m_WindowDetails.Title = specs.Title;
    m_WindowDetails.Width = specs.Width;
    m_WindowDetails.Height = specs.Height;
}