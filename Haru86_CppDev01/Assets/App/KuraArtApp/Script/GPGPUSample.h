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
private:
    std::unique_ptr<class Material> m_material;
    std::unique_ptr<class Mesh> m_mesh;
};

