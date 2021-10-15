#pragma once
#include "./Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "./Game.h"

class TransformComponent :
    public Component
{
public:
    TransformComponent(class Game* g,class Object* o, glm::vec3* pos, glm::quat* rot, glm::vec3* s);
    ~TransformComponent();
    void Update() override;
    glm::mat4 GetMVPMatrix(){ return pMatrix * vMatrix * mMatrix; }
    void CalMatrix();
    void Translate();
    void Rotate();
    void ComputeModelMatrix();
    void ComputeViewMatrix();
    void ComputePerspectiveMatrix();
    glm::vec3* position;
    glm::quat* rotation;
    glm::vec3* scale;
private:
    glm::mat4 mMatrix;
    glm::mat4 vMatrix;
    glm::mat4 pMatrix;
};

