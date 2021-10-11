#pragma once
#include "./Component.h"
class Material :
    public Component
{
public:
    Material(class GameObject* o);
    ~Material();
    void Update() override;
};

