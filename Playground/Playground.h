#pragma once
#include "src/ExampleLayer.h"

class Playground : public Application
{
public:
    Playground()
    {
        PushLayer(new ExampleLayer());
    }
    
private:

};

Application* CreateApplication()
{
    return new Playground();
}