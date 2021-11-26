#pragma once
#include "GraphicsEngine/Component/Component.h"
#include <memory>

class GPGPUSample :
    public Component
{
public:
    GPGPUSample(class Object* o);
    ~GPGPUSample();
    void Start() override;
    void Update() override;
    void ProcessInput(const Uint8* state)const override;
    void Draw();
    friend class KuraArtApp;
private:
    std::unique_ptr<class Material> m_material;
    std::unique_ptr<class Mesh> m_mesh;
    std::unique_ptr<class ComputeBuffer> m_computeBuffer;
    std::unique_ptr<class ComputeShader> m_computeShader;
    int num;
};

