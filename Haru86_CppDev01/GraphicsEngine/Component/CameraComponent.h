#pragma once
#include "Component.h"

class CameraComponent :
    public Component
{
public:
    CameraComponent(class Object* o, enum class CameraType cameraType);
    ~CameraComponent();
    void Start() override;
    void Update() override;
    void ProcessInput(const Uint8* state)const override;
    enum class CameraType m_cameraType;
};

