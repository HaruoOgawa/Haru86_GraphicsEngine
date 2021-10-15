#include "TransformComponent.h"
//#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "./Game.h"

TransformComponent::TransformComponent(Game* g,Object* o, glm::vec3* pos,glm::quat* rot,glm::vec3* s)
	: Component(g,o),position(pos),rotation(rot),scale(s)
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

void TransformComponent::CalMatrix() {
	ComputeModelMatrix();
	ComputeViewMatrix();
	ComputePerspectiveMatrix();
}

void TransformComponent::ComputeModelMatrix() {
	glm::mat4 translationMatirx = glm::translate(glm::mat4(1.0f), glm::vec3(position->x, position->y, position->z));
	glm::mat4 rotationMatrix = glm::mat4_cast(*rotation);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f),glm::vec3(scale->x, scale->y, scale->z));

	mMatrix = translationMatirx* rotationMatrix * scaleMatrix;
}

void TransformComponent::ComputeViewMatrix() {
	vMatrix = glm::lookAt(
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f,1.0f, 0.0f)
	);
}

void TransformComponent::ComputePerspectiveMatrix() {
	pMatrix = glm::perspective(
		glm::radians(60.0f),
		4.0f/3.0f,
		0.1f,
		100.0f
	);
}