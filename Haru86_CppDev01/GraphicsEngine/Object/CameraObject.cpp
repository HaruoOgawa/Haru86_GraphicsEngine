#include "CameraObject.h"
#include "GraphicsEngine/Component/CameraComponent.h"
#include "GraphicsEngine/Game/Game.h"

CameraObject::CameraObject(CameraType cameraType)
	: Object(),m_cameraType(cameraType)
{
	Game::GetInstance()->game_camera_instance = this;
	m_cameraComponent =  std::make_shared<CameraComponent>(this,cameraType);
	AddComponent(m_cameraComponent);
}

CameraObject::~CameraObject() {
	printf("CameraObject is Called\n");
}

void CameraObject::Update() {

}