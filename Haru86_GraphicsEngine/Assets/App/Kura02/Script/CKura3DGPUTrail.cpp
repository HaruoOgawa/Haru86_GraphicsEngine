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
	//force=0 data=1
	//force buffer
	m_computeBuffer_BoidsForce = std::make_shared<ComputeBuffer>(sizeof(BoidsForce) * num);
	std::vector<BoidsForce> forceData;

	//data buffer
	m_computeBuffer_BoidsData = std::make_shared<ComputeBuffer>(sizeof(BoidsData) * num);
	std::vector<BoidsData> resultData;

	for (int i = 0; i < num; i++) {
		float size = 100.0;
		float pos[3] = {
			(rand(glm::vec2(i,0.951)) * 2.0 - 1.0) * size,
			(rand(glm::vec2(i,0.456)) * 2.0 - 1.0) * size,
			(rand(glm::vec2(i,0.753)) * 2.0 - 1.0) * size
		};

		glm::vec3 v = glm::normalize(glm::vec3(
			(rand(glm::vec2(0.321, i)) * 2.0 - 1.0),
			(rand(glm::vec2(0.654, i)) * 2.0 - 1.0),
			(rand(glm::vec2(0.987, i)) * 2.0 - 1.0)
		));
		float vel[3] = {
			v.x,
			v.y,
			v.z
		};

		//force
		forceData.push_back(BoidsForce(vel));

		//data
		resultData.push_back(BoidsData(pos, vel));
	}

	//force attach
	m_computeBuffer_BoidsForce->SetData<std::vector<BoidsForce>>(forceData);

	//data attach
	m_computeBuffer_BoidsData->SetData<std::vector<BoidsData>>(resultData);

	//SetBuffer//////////////
	//force compute
	m_computeShader_force = std::make_shared<ComputeShader>("./Assets/Shader/KuraShader/BoidsForce.comp");
	
	//data compute
	m_computeShader_data = std::make_shared<ComputeShader>("./Assets/Shader/KuraShader/BoidsData.comp");
	
	//clear data
	forceData.clear();
	resultData.clear();
	printf("Start\n");
}

void CKura3DGPUTrail::Update() {
	//Boids/////////////////////////////////////////////////
	//Dispatch force///////////////////////////
	m_computeShader_force->SetActive();
	m_computeShader_force->SetFloatUniform("_time", Game::GetInstance()->time);
	m_computeShader_force->SetFloatUniform("_deltaTime", Game::GetInstance()->deltaTime);
	//boid uniform
	m_computeShader_force->SetFloatUniform("_centerPosPower", 1000000.0);
	m_computeShader_force->SetFloatUniform("_maxBoidsDist", 50);

	//ŽÀÛ‚ÉŽg‚Á‚Ä‚¢‚éuniform
	m_computeShader_force->SetIntUniform("_boids_count", num);
	m_computeShader_force->SetFloatUniform("_maxBoidsField", 200);
	m_computeShader_force->SetFloatUniform("_NoiseValue", 0.1);
	m_computeShader_force->SetFloatUniform("_joinPower", 100);
	m_computeShader_force->SetFloatUniform("_separatePower", 1000);
	m_computeShader_force->SetFloatUniform("_alignmentPower", 100);
	m_computeShader_force->SetFloatUniform("_joinDisMin", 0.1);  // pre10
	m_computeShader_force->SetFloatUniform("_separateDistMin", 1000); //pre10
	m_computeShader_force->SetFloatUniform("_alignmentDistMin", 0.1); //pre10
	m_computeShader_force->Dispatch(num / 256, 1, 1);

	//Dispatch Data///////////////
	m_computeShader_data->SetActive();
	m_computeShader_data->SetFloatUniform("_time", Game::GetInstance()->time);
	m_computeShader_data->SetFloatUniform("_deltaTime", Game::GetInstance()->deltaTime);
	//boid uniform
	m_computeShader_data->Dispatch(num / 256, 1, 1);
	////////////////////////////////////////////////////////
}

void CKura3DGPUTrail::Draw() {
}

void CKura3DGPUTrail::ProcessInput(const Uint8* state)const {

}

float CKura3DGPUTrail::rand(glm::vec2 st) {
	return glm::fract(glm::sin(glm::dot(st, glm::vec2(12.9898, 78.233))) * 43758.5453);
}