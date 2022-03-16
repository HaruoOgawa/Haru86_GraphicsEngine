#pragma once
#include "GraphicsEngine/Component/Component.h"
#include <memory>
#include <string>
#include <vector>

class ComputeBuffer;

struct SCubeFieldObj
{
public:
    int xIndex;
    int yIndex;
    int instancedIndex;
    SCubeFieldObj(int x, int y, int ii)
        :
        xIndex(x),
        yIndex(y),
        instancedIndex(ii)
    {
    }
};

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
    int sideCubeCount;
    std::shared_ptr<ComputeBuffer> m_cubeGroundBuffer;
};

