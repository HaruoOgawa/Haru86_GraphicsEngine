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
#include "GraphicsEngine/Object/CameraObject.h"
#include "GraphicsEngine/Component/CameraComponent.h"
#include "GraphicsEngine/Graphics/Texture.h"

KuraTrail::KuraTrail(Object* o, KuraGPGPU* kuraGPGPU)
	: Component(o, static_cast<std::string>(typeid(KuraTrail).name()).substr(6)),
	kuraGPGPU_instance(kuraGPGPU),
	trailNum(kuraGPGPU->num),
	nodeSegment(512)
{
	nodeNum = trailNum * nodeSegment;
	
	m_material = std::make_unique<Material>(
		"./Assets/Shader/KuraShader/GPUTrail_Render.vert",
		"./Assets/Shader/KuraShader/GPUTrail_Render.geom",
		"./Assets/Shader/KuraShader/GPUTrail_Render.frag"		
	);

	m_texture_trail = std::make_unique<Texture>();
	if (!m_texture_trail->Load("./Assets/Resources/glTFData/Phoenix_Blender/PosTex.png")) {
		printf("Cannot Load Texture\n");
	}

	m_mesh = std::make_unique<Mesh>(PrimitiveType::POINT);
	
	//compute shader
	m_computeShader_NextInputPos = std::make_unique<ComputeShader>("./Assets/Shader/KuraShader/GPUTrail_NextInputPos.comp");
	m_computeShader_NodeInfo = std::make_unique<ComputeShader>("./Assets/Shader/KuraShader/GPUTrail_NodeInfo.comp");

	//compute buffer
	m_buffer_trail = std::make_unique<ComputeBuffer>(sizeof(trail)* trailNum);
	m_buffer_node = std::make_unique<ComputeBuffer>(sizeof(node)* nodeNum);
	m_buffer_input = std::make_unique<ComputeBuffer>(sizeof(input_data)* trailNum);

	Start();
}

KuraTrail::~KuraTrail() {

}

void KuraTrail::Start() {
	//init buffer data
	std::vector<trail> init_trail = std::vector<trail>(trailNum, trail(0, nodeSegment));
	float input_pos[3] = { 0.0,0.0,0.0 };
	std::vector<input_data> init_input_data = std::vector<input_data>(trailNum, input_data(input_pos));
	
	std::vector<node> init_node;
	float initPos[3] = { 0,0,0 };
	float initvel[3] = { 0,0,0 };
	std::vector<BoidsData> init_boidsData = std::vector<BoidsData>(trailNum, BoidsData(initPos, initvel));
	kuraGPGPU_instance->m_computeBuffer_BoidsData->GetBufferData(&init_boidsData[0], 0, trailNum);

	for (int i = 0; i < trailNum;i++) {
		float boids_pos[3] = { init_boidsData[i].position[0],init_boidsData[i].position[1],init_boidsData[i].position[2] };
		for (int q = 0; q < nodeSegment; q++) {
			init_node.push_back(node(boids_pos, 5));
		}
	}

	init_boidsData.clear();

	//set init data to buffer
	m_buffer_trail->SetData<std::vector<trail>>(init_trail);
	m_buffer_node->SetData<std::vector<node>>(init_node);
	m_buffer_input->SetData<std::vector<input_data>>(init_input_data);

	//clear init data
	init_trail.clear();
	init_input_data.clear();
	init_node.clear();

	//next input
	m_computeShader_NextInputPos->SetBuffer(kuraGPGPU_instance->m_computeBuffer_BoidsData.get(), 1, m_material.get());
	m_computeShader_NextInputPos->SetBuffer(m_buffer_input.get(), 2, m_material.get());
	//node info
	m_computeShader_NodeInfo->SetBuffer(m_buffer_node.get(), 3, m_material.get());
	m_computeShader_NodeInfo->SetBuffer(m_buffer_trail.get(), 4, m_material.get());

	//set buffer to material
	m_material->SetBuffer(m_buffer_node.get(), 3);
	m_material->SetBuffer(m_buffer_trail.get(), 4);

}

void KuraTrail::Update() {
	//NextInputPos
	m_computeShader_NextInputPos->SetActive();
	m_computeShader_NextInputPos->Dispatch(trailNum/256,1,1);

	//NodeInfo
	m_computeShader_NodeInfo->SetActive();
	m_computeShader_NodeInfo->SetIntUniform("_nodeSegment", nodeSegment);
	m_computeShader_NodeInfo->SetFloatUniform("_nodeDistanceMin", 1);
	m_computeShader_NodeInfo->SetFloatUniform("_time",Game::GetInstance()->time );
	m_computeShader_NodeInfo->SetFloatUniform("_initNodeLife", 5.0);
	m_computeShader_NodeInfo->Dispatch(trailNum / 256, 1, 1);

}

void KuraTrail::ProcessInput(const Uint8* state)const {

}

void KuraTrail::Draw() {
	m_texture_trail->SetActive();
	m_material->SetTexUniform("_trailTex", m_texture_trail->GetTextureID());
	
	owner->transform->CalMatrix();
	m_material->SetActive();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glDisable(GL_DEPTH_TEST);
	m_material->SetMatrixUniform("MVPMatrix", owner->transform->GetMVPMatrix()); 
	m_material->SetMatrixUniform("MMatrix", owner->transform->GetMMatrix());
	m_material->SetMatrixUniform("VMatrix", owner->transform->GetVMatrix());
	m_material->SetMatrixUniform("PMatrix", owner->transform->GetPMatrix());
	m_material->SetFloatUniform("_time", Game::GetInstance()->time);
	m_material->SetFloatUniform("_deltaTime", Game::GetInstance()->deltaTime);

	//GPU Trail Uniform
	m_material->SetVec3Uniform("_WorldSpaceCameraPos",Game::GetInstance()->game_camera_instance->transform->position);
	m_material->SetFloatUniform("_initNodeLife", 5);
	m_material->SetFloatUniform("_nodeSegment",nodeSegment );
	m_material->SetFloatUniform("_TrailWidth", 0.5);
	m_material->SetIntUniform("_boids_count", nodeNum);
	Graphics::DrawInstancedWithMesh(m_mesh.get(), nodeNum, m_material.get(), GL_POINTS);
}