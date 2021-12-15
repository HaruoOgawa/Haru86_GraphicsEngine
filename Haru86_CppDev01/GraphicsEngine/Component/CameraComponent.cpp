#include "CameraComponent.h"
#include "GraphicsEngine/Object/CameraObject.h"

CameraComponent::CameraComponent(std::shared_ptr<Object> o, enum class CameraType cameraType)
	: Component(o, static_cast<std::string>(typeid(CameraComponent).name()).substr(6))
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