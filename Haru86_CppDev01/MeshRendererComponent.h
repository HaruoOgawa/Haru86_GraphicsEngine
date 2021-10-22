#pragma once
#include "./Component.h"
#include "./Object.h"
#include "./VertexArray.h"
#include "./Material.h"
#include <string>
#include "./Primitive.h"
#include "./Game.h"

class MeshRendererComponent :
    public Component
{
public:
    MeshRendererComponent(class Object* o,PrimitiveType primType);
    MeshRendererComponent(class Object* o, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName);
    ~MeshRendererComponent();
    void Update() override;
    void Draw();
    bool useZTest;
private:
    VertexArray* mesh;
    Material* material;
    class Object* myowner;
};

