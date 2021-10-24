#pragma once
#include "Component.h"
class UIComponent :
    public Component
{
public:
    UIComponent(class GameObject* o);
    ~UIComponent();
    void Update() override;
    void ProcessInput(const Uint8* state)const override;
private:
    bool CheckInnnerBox( float x, float y)const;
};

