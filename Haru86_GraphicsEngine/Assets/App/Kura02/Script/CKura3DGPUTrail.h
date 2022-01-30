#pragma once
#include "GraphicsEngine/Component/Component.h"

class Object;

class CKura3DGPUTrail :
    public Component
{

public:
    CKura3DGPUTrail(Object* o);
    ~CKura3DGPUTrail();
    void Start() override;
    void Update() override;
    void Draw();
    void ProcessInput(const Uint8* state)const override;
};

