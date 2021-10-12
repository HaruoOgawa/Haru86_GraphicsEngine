#pragma once
#include "./Component.h"
#include "./Object.h"
#include "./VertexArray.h"
#include "./Material.h"

class MeshRendererComponent :
    public Component
{
public:
    MeshRendererComponent(class Object* o);
    ~MeshRendererComponent();
    void Update() override;
    void Draw();
private:
    VertexArray* mesh;
    Material* material;
};

