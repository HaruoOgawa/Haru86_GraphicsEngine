#pragma once
#include "./Component.h"
#include "./Object.h"

class MeshRendererComponent :
    public Component
{
public:
    MeshRendererComponent(class Object* o);
    ~MeshRendererComponent();
    void Update() override;
    void Draw();
};

