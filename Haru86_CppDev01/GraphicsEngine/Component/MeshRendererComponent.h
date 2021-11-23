#pragma once
#include "../Component/Component.h"
#include "../Object/Object.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Material.h"
#include <string>
#include "../Graphics/Primitive.h"
#include "../Game/Game.h"
#include <functional>

class MeshRendererComponent :
    public Component
{
public:
    MeshRendererComponent(class Object* o,PrimitiveType primType);
    MeshRendererComponent(class Object* o, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName);
    MeshRendererComponent(class Object* o, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName, std::string textureString);
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
    Mesh* mesh;
    class Texture* primTex;
    class Object* myowner;
};

