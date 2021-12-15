#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <memory>

class CameraComponent :
    public Component
{
public:
    CameraComponent(std::shared_ptr<class Object> o, enum class CameraType cameraType);
    ~CameraComponent();
    void Start() override;
    void Update() override;
    void ProcessInput(const Uint8* state)const override;
    enum class CameraType m_cameraType;
    glm::vec3 cameraCenter;
    glm::vec3 cameraUp;
};

