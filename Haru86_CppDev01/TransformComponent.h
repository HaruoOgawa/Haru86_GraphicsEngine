#pragma once
#include "./Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class TransformComponent :
    public Component
{
public:
    TransformComponent(Object* o, glm::vec3* pos, glm::quat* rot, glm::vec3* s);
    ~TransformComponent();
    void Update() override;
    void Translate();
    void Rotate();
    glm::vec3* position;
    glm::quat* rotation;
    glm::vec3* scale;
private:
    
};

