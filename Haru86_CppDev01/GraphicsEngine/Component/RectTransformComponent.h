#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <memory>

class RectTransformComponent :
    public Component
{
public:
    RectTransformComponent(class GameObject* o,float wRate,float hRate);
    ~RectTransformComponent();
    void ProcessInput(const Uint8* state)const override;
    glm::vec2 rectPosition;
    glm::vec2 rectScale;
    float maxLeftPointX;
    float maxRightPointX;
};

