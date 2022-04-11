#include "CPhysicsEngine.h"
#include "CColliderTree.h"
#include "GraphicsEngine/Object/GameObject.h"
#include "ACollider.h"
#include "GraphicsEngine/Component/TransformComponent.h"
#include "GraphicsEngine/GraphicsMain/GraphicsMain.h"

#define gravityVal 9.80665f 

namespace physics {
	CPhysicsEngine::CPhysicsEngine() :
		m_ColliderTree(std::make_unique<CColliderTree>())
	{

	}

	CPhysicsEngine::~CPhysicsEngine() {
		Release();
	}

	void CPhysicsEngine::Release() {

	}

	bool CPhysicsEngine::Initialize() {
		if (!m_ColliderTree->MakeColliderTree())return false;

		for (const auto& Collider : m_ColliderTree->GetColliderList()) {
			if (Collider->GetObjectType() == EObjectType::DYNAMIC)m_DynamicColliderList.push_back(Collider);
		}

		return true;
	}

	bool CPhysicsEngine::UpdatePhysics() {

		for (auto& Collider : m_DynamicColliderList) {
			if (!AddForce(Collider))return false;
			if (!m_ColliderTree->DetectCollider(Collider))return false;
			if (!UpdatePosition(Collider))return false;
		}

		return true;
	}

	void CPhysicsEngine::AddCollider(EColliderType ColliderType, EObjectType ObjectType, GameObject* Obj) {
		m_ColliderTree->AddCollider(ColliderType, ObjectType, Obj);
	}

	bool CPhysicsEngine::AddForce(std::shared_ptr<ACollider> Collider) {
		glm::vec3 force = glm::vec3(0.0f);

		// d—Í
		force += Collider->GetMass() * (-1.0f * glm::vec3(0.0f, gravityVal,0.0f));

		Collider->SetForce(force);

		return true;
	}

	bool CPhysicsEngine::UpdatePosition(std::shared_ptr<ACollider> Collider) {
		glm::vec3 UpdatePos = Collider->GetTransform()->GetPosition();
		UpdatePos += (Collider->GetForce() / Collider->GetMass())* GraphicsMain::GetInstance()->deltaTime;

		Collider->GetTransform()->SetPosition(UpdatePos);
		return true;
	}
}