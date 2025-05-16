#pragma once
#include "Layer.h"
#include <vector>

class LayerStack
{
public:
    ~LayerStack();
    void PushLayer(Layer* layer);
    void PopLayer(Layer* layer);

    std::vector<Layer*>::iterator begin() {return m_Layers.begin();}
    std::vector<Layer*>::iterator end() {return m_Layers.end();}
private:
    std::vector<Layer*> m_Layers;
    int m_LayerInsertIndex = 0;
};