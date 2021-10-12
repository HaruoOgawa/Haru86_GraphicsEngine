#include "TransformComponent.h"
#include <glm/glm.hpp>

TransformComponent::TransformComponent(Object* o, glm::vec3* pos,glm::quat* rot,glm::vec3* s)
	: Component(o),position(pos),rotation(rot),scale(s)
{

}

TransformComponent::~TransformComponent() {
	delete position;
	delete rotation;
	delete scale;
}

void TransformComponent::Update() {

}

void TransformComponent::Translate() {

}
void TransformComponent::Rotate() {

}