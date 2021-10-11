#pragma once
#include "./Component.h"
class Mesh :
    public Component
{
public:
    Mesh(class GameObject* o);
    ~Mesh();
    void Update() override;
};

