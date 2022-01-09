#pragma once
#include "GraphicsEngine/Component/Component.h"
class CBoxInstancing :
    public Component
{
public:
    CBoxInstancing(Object* o);
    ~CBoxInstancing();
    void Start() override;
    void Update() override;
    void ProcessInput(const Uint8* state)const override;
};

