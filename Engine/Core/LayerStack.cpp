#include "LayerStack.h"

#include <algorithm>
#include <iostream>

void LayerStack::PushLayer(Layer* layer)
{
    // TODO Emplace 
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
    m_LayerInsertIndex++;
}

void LayerStack::PopLayer(Layer* layer)
{
    auto it = std::find(begin(), end(), layer);
    if (it != end()) 
    {
        m_Layers.erase(it);
        m_LayerInsertIndex--;
    }

}

LayerStack::~LayerStack()
{
    for(Layer* layer : m_Layers)
    {
        PopLayer(layer);
    }
}