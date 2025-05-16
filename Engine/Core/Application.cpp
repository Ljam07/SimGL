#include "Application.h"

Application::Application()
    : m_Window(Window())
{
    m_Window.CreateWindow();
}

void Application::Run()
{
    while (!m_Window.ShouldWindowClose())
    {
        float time = (float)glfwGetTime();
        DeltaTime deltaTime = time - m_LastFrameTime;
        m_LastFrameTime = time;

        for (Layer* layer : m_LayerStack)
        {
            layer->OnUpdate(deltaTime);
        }

        m_Window.OnUpdate();
    }

}

void Application::PushLayer(Layer* layer)
{
    layer->OnAttach();
    m_LayerStack.PushLayer(layer);
}