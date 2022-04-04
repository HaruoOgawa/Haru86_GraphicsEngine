#pragma once
#include "Component.h"
#include <memory>

class UIComponent :
    public Component
{
public:
    UIComponent(class GameObject* o);
    ~UIComponent();
    void Update() override;
    void ProcessInput(const Uint8* state) override;
private:
    bool CheckInnnerBox( float x, float y)const;
};

