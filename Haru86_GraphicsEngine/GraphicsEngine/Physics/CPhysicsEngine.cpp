#include "CPhysicsEngine.h"
#include "CColliderTree.h"
#include "GraphicsEngine/Object/GameObject.h"

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

		return true;
	}

	bool CPhysicsEngine::UpdatePhysics() {
		return true;
	}

	void CPhysicsEngine::AddCollider(EColliderType ColliderType, GameObject* Obj) {
		m_ColliderTree->AddCollider(ColliderType, Obj);
	}
}