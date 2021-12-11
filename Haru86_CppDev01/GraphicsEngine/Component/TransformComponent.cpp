#include "TransformComponent.h"
//#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "../Game/Game.h"
#include "../Graphics/GameRenderer.h"
#include "GraphicsEngine/Object/CameraObject.h"
#include "GraphicsEngine/Component/CameraComponent.h"

TransformComponent::TransformComponent(Object* o, glm::vec3 pos,glm::quat rot,glm::vec3 s)
	: Component(o, static_cast<std::string>(typeid(TransformComponent).name()).substr(6)),position(pos),rotation(rot),scale(s)
{
	CalMatrix();
}

TransformComponent::~TransformComponent() {
	/*delete position;
	delete rotation;
	delete scale;*/
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
	glm::mat4 translationMatirx = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
	glm::mat4 rotationMatrix = glm::mat4_cast(rotation);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f),glm::vec3(scale.x, scale.y, scale.z));

	mMatrix = translationMatirx* rotationMatrix * scaleMatrix;
}

void TransformComponent::ComputeViewMatrix() {
	if (Game::GetInstance()->game_camera_instance!=nullptr) {
		CameraObject* cam = Game::GetInstance()->game_camera_instance;
		vMatrix = glm::lookAt(
			cam->transform->position,
			cam->m_cameraComponent->cameraCenter,
			cam->m_cameraComponent->cameraUp
		);
	}
	else {
		vMatrix = glm::lookAt(
			glm::vec3(0.0f, 0.0f, -3.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
	}
	
	
}

void TransformComponent::ComputePerspectiveMatrix() {
	float width = static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().x);
	float height = static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().y);
	
	pMatrix = glm::perspective(
		glm::radians(120.0f),
		width/height,
		0.1f,
		3000.0f
	);
}

void TransformComponent::ProcessInput(const Uint8* state)const {

}