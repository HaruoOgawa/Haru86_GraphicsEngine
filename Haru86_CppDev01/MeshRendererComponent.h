#pragma once
#include "./Component.h"
#include "./Object.h"
#include "./VertexArray.h"
#include "./Material.h"
#include <string>
#include "./Primitive.h"
#include "./Game.h"
#include <functional>

class MeshRendererComponent :
    public Component
{
public:
    MeshRendererComponent(class Object* o,PrimitiveType primType);
    MeshRendererComponent(class Object* o, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName);
    ~MeshRendererComponent();
    void Update() override;
    void Draw();
    void DrawBoard();
    void ProcessInput(const Uint8* state)const override;
    bool useZTest;
    std::vector<class TimelineAnimationClip*> animationClips;
    Material* material;
    friend class GameRenderer;
private:
    VertexArray* mesh;
   
    class Object* myowner;
};

