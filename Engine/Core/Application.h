#pragma once
#include <iostream>

#include "Window.h"
#include "LayerStack.h"
#include "DeltaTime.h"

class Application
{
public:
    Application();
    //~Application();

    void PushLayer(Layer* layer);

    void Run();
private:
    Window m_Window;
    LayerStack m_LayerStack;
    float m_LastFrameTime = 0.0f;
};

Application* CreateApplication();