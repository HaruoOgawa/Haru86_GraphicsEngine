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
    MeshRendererComponent(std::shared_ptr<class Object> o,PrimitiveType primType);
    MeshRendererComponent(std::shared_ptr<class Object> o,PrimitiveType primType, std::map<GLenum, std::string> shaders);
    MeshRendererComponent(std::shared_ptr<class Object> o, std::string objPath);
    MeshRendererComponent(std::shared_ptr<class Object> o, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName);
    MeshRendererComponent(std::shared_ptr<class Object> o, PrimitiveType primType, std::string vertexShaderName, std::string tessellationShaderName[2], std::string fragmentShaderName);
    MeshRendererComponent(std::shared_ptr<class Object> o, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName, std::string textureString);
    MeshRendererComponent(std::shared_ptr<class Object> o,std::string modelDataPath, std::string vertexShaderName, std::string fragmentShaderName);
    ~MeshRendererComponent();
    void Update() override;
    void Draw();
    void DrawBoard();
    void ProcessInput(const Uint8* state)const override;
    bool useZTest;
    std::vector<std::shared_ptr<class TimelineAnimationClip>> animationClips;
    std::shared_ptr<class Material> material;
    friend class GameRenderer;
private:
    std::unique_ptr<Mesh> mesh;
    std::shared_ptr<class Texture> primTex;
    std::shared_ptr<class Object> myowner;
};

