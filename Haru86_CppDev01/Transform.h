#pragma once
#include "./Component.h"

class Transform :
    public Component
{
public:
    Transform(class GameObject* o);
    ~Transform();
    void Update() override;
};

