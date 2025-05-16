#pragma once
#include <string>

#include "DeltaTime.h"

class Layer
{
public:
    Layer(const std::string& debugName = "Layer") : m_Name(debugName) {}

    virtual void OnAttach() = 0;

    // TODO deltaTime
    virtual void OnUpdate(DeltaTime deltaTime) = 0;

    const std::string& GetName() const {return m_Name;}
private:
    std::string m_Name;
};