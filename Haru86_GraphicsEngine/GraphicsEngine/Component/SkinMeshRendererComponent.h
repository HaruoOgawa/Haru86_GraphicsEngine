#pragma once
#include "ARendererComponent.h"

class SkinMeshRendererComponent :
	public ARendererComponent
{
public:
	SkinMeshRendererComponent(Object* o, std::string objPath, std::string vertexShaderName= "./Assets/Shader/MToon.vert", std::string fragmentShaderName= "./Assets/Shader/MToon.frag");
	~SkinMeshRendererComponent();

	virtual void Update() override;
	virtual void Draw() override;
	virtual void ProcessInput(const SDL_Event& e) override;
};