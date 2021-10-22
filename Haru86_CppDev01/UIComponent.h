#pragma once
#include "Component.h"
class UIComponent :
    public Component
{
public:
    UIComponent(class GameObject* o);
    ~UIComponent();
    void ProcessInput(const Uint8* state)const override;
};

