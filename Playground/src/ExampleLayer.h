#pragma once
#include "../../Engine/Core/Application.h"
#include "../../Engine/Core/Layer.h"
#include "../../Engine/Core/DeltaTime.h"

class ExampleLayer : public Layer
{
public:
    void OnAttach();

    void OnUpdate(DeltaTime deltaTime);
private:

};