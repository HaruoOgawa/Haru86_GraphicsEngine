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
		return true;
	}

	bool CPhysicsEngine::UpdatePhysics() {
		return true;
	}

	void CPhysicsEngine::AddCollider(EColliderType ColliderType, GameObject* Obj) {

	}
}