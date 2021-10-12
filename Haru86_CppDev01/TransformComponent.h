#pragma once
#include "./Component.h"

class TransformComponent :
    public Component
{
public:
    TransformComponent(class Object* o);
    ~TransformComponent();
    void Update() override;
};

