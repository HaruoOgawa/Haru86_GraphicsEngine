#pragma once
#include "./Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "../Game/Game.h"
#include <memory>

class TransformComponent :
    public Component
{
public:
    TransformComponent(class Object* o, glm::vec3 pos, glm::quat rot, glm::vec3 s);
    ~TransformComponent();
    void Update() override;
    glm::mat4 GetMVPMatrix(){ return pMatrix * vMatrix * mMatrix; }
    glm::mat4 GetMMatrix(){ return mMatrix; }
    glm::mat4 GetVMatrix() { return vMatrix; }
    glm::mat4 GetPMatrix(){ return pMatrix; }
    void CalMatrix();
    void Translate(glm::vec3 MoveV);
    void Rotate(float XRot, float YRot, float ZRot);
    void ComputeModelMatrix();
    void ComputeViewMatrix();
    void ComputePerspectiveMatrix();
    void ProcessInput(const SDL_Event& e) override;
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    glm::mat4 mMatrix;
    glm::mat4 vMatrix;
    glm::mat4 pMatrix;
private:
   
};

