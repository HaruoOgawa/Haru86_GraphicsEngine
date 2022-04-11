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
		ReleaseLoopResource();
		m_DynamicColliderList.clear();
		m_ColliderTree.release();
	}

	void CPhysicsEngine::ReleaseLoopResource() {
		m_CollisionInfoList.clear();
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
			if (!DetectCollider(Collider))return false;
			// 貫通を解消する
			if (!UpdatePosition(Collider))return false;
			ReleaseLoopResource(); // このループで作成したコリジョンのリソースを開放する
		}

		return true;
	}

	void CPhysicsEngine::AddCollider(EColliderType ColliderType, EObjectType ObjectType, GameObject* Obj) {
		m_ColliderTree->AddCollider(ColliderType, ObjectType, Obj);
	}

	bool CPhysicsEngine::AddForce(std::shared_ptr<ACollider> Collider) {
		glm::vec3 force = glm::vec3(0.0f);
		glm::vec3 velocity = Collider->GetVelocity();

		// 加わる力を計算する
		force += Collider->GetMass() * (-1.0f * glm::vec3(0.0f, gravityVal,0.0f));
		Collider->SetForce(force);

		// 速度
		velocity += (Collider->GetForce() / Collider->GetMass()) * GraphicsMain::GetInstance()->deltaTime;
		Collider->SetVelocity(velocity);

		return true;
	}

	bool CPhysicsEngine::DetectCollider(std::shared_ptr<ACollider> Collider) {
		// コライダーツリーから衝突しそうなコライダーリストを取得する
		const auto PassiveColliderList = m_ColliderTree->GetPassiveColliderListFromTree(Collider);

		// 各コライダーに対して衝突判定を行う
		for (const auto& PassiveCollider : PassiveColliderList) {
			auto CollisionInfo= PassiveCollider->DetectCollider(Collider);
			if (CollisionInfo)m_CollisionInfoList.push_back(CollisionInfo);
		}

		return true;
	}

	bool CPhysicsEngine::UpdatePosition(std::shared_ptr<ACollider> Collider) {
		glm::vec3 UpdatePos = Collider->GetTransform()->GetPosition();
		UpdatePos += Collider->GetVelocity()* GraphicsMain::GetInstance()->deltaTime;

		Collider->GetTransform()->SetPosition(UpdatePos);
		return true;
	}
}