#pragma once
#include "GraphicsEngine/Component/Component.h"
#include <memory>
#include <string>

class CBoxInstancing :
    public Component
{
public:
    CBoxInstancing(Object* o);
    ~CBoxInstancing();
    void Start() override;
    void Update() override;
    void Draw();
    void ProcessInput(const Uint8* state)const override;
private:
    std::shared_ptr<class Mesh> m_mesh;
    std::shared_ptr<class Material> m_material;
    int instanciedCound;
};

