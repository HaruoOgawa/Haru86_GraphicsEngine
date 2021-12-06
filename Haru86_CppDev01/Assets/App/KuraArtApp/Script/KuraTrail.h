#pragma once
#include "GraphicsEngine/Component/Component.h"

class KuraTrail : 
	public Component
{
public:
    KuraTrail(class Object* o);
    ~KuraTrail();
    void Start() override;
    void Update() override;
    void ProcessInput(const Uint8* state)const override;
    void Draw();
};

