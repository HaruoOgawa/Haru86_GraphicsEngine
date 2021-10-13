#pragma once
#include "./Component.h"
#include "./Object.h"
#include "./VertexArray.h"
#include "./Material.h"
#include <string>

class MeshRendererComponent :
    public Component
{
public:
    MeshRendererComponent(class Object* o, std::string vertexShaderName, std::string fragmentShaderName);
    ~MeshRendererComponent();
    void Update() override;
    void Draw();
private:
    VertexArray* mesh;
    Material* material;
};

