#pragma once
#include "Component.h"

class CameraComponent :
    public Component
{
public:
    CameraComponent(class Object* o);
    ~CameraComponent();
    void Start() override;
    void Update() override;
    void ProcessInput(const Uint8* state)const override;
};

