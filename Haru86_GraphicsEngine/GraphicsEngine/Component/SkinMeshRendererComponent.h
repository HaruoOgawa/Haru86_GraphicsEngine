#pragma once
#include "ARendererComponent.h"
#include <glm/glm.hpp>

namespace animation {
	class Skeleton;
	class Pose;
}

class SkinMeshRendererComponent :
	public ARendererComponent
{
	std::shared_ptr<animation::Skeleton> m_Skeleton;
	std::vector<glm::mat4> m_PoseMatrix;
	animation::Pose m_CurrentPose;

public:
	SkinMeshRendererComponent(Object* o, std::string objPath, std::string vertexShaderName= "./Assets/Shader/MToon.vert", std::string fragmentShaderName= "./Assets/Shader/MToon.frag");
	~SkinMeshRendererComponent();

	virtual void Update() override;
	virtual void Draw() override;
	virtual void ProcessInput(const SDL_Event& e) override;
};