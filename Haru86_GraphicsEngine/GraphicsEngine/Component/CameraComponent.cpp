#include "CameraComponent.h"
#include "GraphicsEngine/Object/CameraObject.h"

CameraComponent::CameraComponent(Object* o, enum class CameraType cameraType)
	: Component(o)
	, m_cameraType(cameraType), cameraCenter(glm::vec3(0.0f, 0.0f, 0.0f)),cameraUp(glm::vec3(0.0f, 1.0f, 0.0f))
{

}

CameraComponent::~CameraComponent() {
}

void CameraComponent::Start() {

}

void CameraComponent::Update() {

}

void CameraComponent::ProcessInput(const Uint8* state)const {

}