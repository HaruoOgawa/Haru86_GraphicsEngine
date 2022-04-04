#pragma once
#include "../Component/Component.h"
#include "../Object/Object.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Material.h"
#include <string>
#include "../Graphics/Primitive.h"
#include "../Game/Game.h"
#include <functional>
#include <memory>

class MeshRendererComponent :
    public Component
{
public:
    MeshRendererComponent(class Object* o,PrimitiveType primType);
    MeshRendererComponent(class Object* o,PrimitiveType primType, std::map<GLenum, std::string> shaders);
    MeshRendererComponent(class Object* o, std::string objPath);
    MeshRendererComponent(class Object* o, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName);
    MeshRendererComponent(class Object* o, PrimitiveType primType, std::string vertexShaderName, std::string tessellationShaderName[2], std::string fragmentShaderName);
    MeshRendererComponent(class Object* o, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName, std::string textureString);
    MeshRendererComponent(class Object* o,std::string modelDataPath, std::string vertexShaderName, std::string fragmentShaderName);
    ~MeshRendererComponent();
    void Update() override;
    void Draw();
    void DrawBoard();
    void ProcessInput(const SDL_Event& e) override;
    bool useZTest;
    std::vector<class TimelineAnimationClip*> animationClips;
    std::shared_ptr<class Material> material;
    friend class GraphicsRenderer;
private:
    std::unique_ptr<Mesh> mesh;
    std::unique_ptr<class Texture> primTex;
    class Object* myowner;
};

