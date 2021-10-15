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
    MeshRendererComponent(class Game* g,class Object* o,PrimitiveType primType);
    MeshRendererComponent(class Game* g,class Object* o, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName);
    ~MeshRendererComponent();
    void Update() override;
    void Draw();
private:
    VertexArray* mesh;
    Material* material;
    class Object* myowner;
};

