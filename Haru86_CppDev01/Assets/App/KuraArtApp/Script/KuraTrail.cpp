#include "KuraTrail.h"
#include <string>
#include "GraphicsEngine/Graphics/Material.h"
#include "GraphicsEngine/Graphics/Mesh.h"
#include "GraphicsEngine/Graphics/Graphics.h"
#include "GraphicsEngine/Object/Object.h"
#include "GraphicsEngine/Component/TransformComponent.h"
#include "GraphicsEngine/Game/Game.h"
#include "../KuraArtApp.h"
#include "GraphicsEngine/Graphics/ComputeBuffer.h"
#include "GraphicsEngine/Graphics/ComputeShader.h"
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "GraphicsEngine/Graphics/Texture.h"
#include "./Assets/App/KuraArtApp/Script/KuraGPGPU.h"

KuraTrail::KuraTrail(Object* o, KuraGPGPU* kuraGPGPU)
	: Component(o, static_cast<std::string>(typeid(KuraTrail).name()).substr(6)),
	kuraGPGPU_instance(kuraGPGPU),
	nodeSegment(512)
{
	num = kuraGPGPU->num * nodeSegment;

	m_material = std::make_unique<Material>(
		"./Assets/Shader/KuraShader/GPUTrail_Render.vert",
		"./Assets/Shader/KuraShader/GPUTrail_Render.geom",
		"./Assets/Shader/KuraShader/GPUTrail_Render.frag"		
	);

	m_mesh = std::make_unique<Mesh>(PrimitiveType::POINT);

	Start();
}

KuraTrail::~KuraTrail() {

}

void KuraTrail::Start() {
	
}

void KuraTrail::Update() {

}

void KuraTrail::ProcessInput(const Uint8* state)const {

}

void KuraTrail::Draw() {
	owner->transform->CalMatrix();
	owner->transform->CalMatrix();
	m_material->SetActive();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	m_material->SetMatrixUniform("MVPMatrix", owner->transform->GetMVPMatrix()); 
	m_material->SetMatrixUniform("MMatrix", owner->transform->GetMMatrix());
	m_material->SetMatrixUniform("VMatrix", owner->transform->GetVMatrix());
	m_material->SetMatrixUniform("PMatrix", owner->transform->GetPMatrix());
	m_material->SetFloatUniform("_time", Game::GetInstance()->time);
	m_material->SetFloatUniform("_deltaTime", Game::GetInstance()->deltaTime);
	m_material->SetIntUniform("_boids_count", num);
	Graphics::DrawInstancedWithMesh(m_mesh.get(), num, m_material.get(), GL_POINTS);
}