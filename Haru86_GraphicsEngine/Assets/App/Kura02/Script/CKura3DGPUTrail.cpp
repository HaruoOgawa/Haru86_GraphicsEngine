#include "GraphicsEngine/Object/Object.h"
#include "CKura3DGPUTrail.h"
#include "GraphicsEngine/Graphics/ComputeShader.h"
#include "GraphicsEngine/Graphics/ComputeBuffer.h"
#include "GraphicsEngine/Graphics/Material.h"
#include "GraphicsEngine/Graphics/Mesh.h"

CKura3DGPUTrail::CKura3DGPUTrail(Object* o)
	: Component(o, static_cast<std::string>(typeid(CKura3DGPUTrail).name()).substr(6)),
	num(256),
	m_computeBuffer_BoidsForce(nullptr),
	m_computeBuffer_BoidsData(nullptr),
	m_computeShader_force(nullptr),
	m_computeShader_data(nullptr),
	m_material(nullptr),
	m_mesh(nullptr),
	m_buffer_trail(nullptr),
	m_buffer_node(nullptr),
	m_buffer_input(nullptr),
	m_computeShader_NextInputPos(nullptr),
	m_computeShader_NodeInfo(nullptr),
	trailNum(256),
	nodeNum(256),
	nodeSegment(256)
{
	Start();
}

CKura3DGPUTrail::~CKura3DGPUTrail() {
}

void CKura3DGPUTrail::Start() {

}

void CKura3DGPUTrail::Update() {

}

void CKura3DGPUTrail::Draw() {

}

void CKura3DGPUTrail::ProcessInput(const Uint8* state)const {

}

float CKura3DGPUTrail::rand(glm::vec2 st) {
	return glm::fract(glm::sin(glm::dot(st, glm::vec2(12.9898, 78.233))) * 43758.5453);
}