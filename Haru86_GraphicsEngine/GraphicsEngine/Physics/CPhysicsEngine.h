#pragma once
#include <vector>
#include <memory>
#include "EColliderType.h"

class GameObject;

namespace physics {
	class CColliderTree;

	class CPhysicsEngine
	{
		std::unique_ptr<CColliderTree> m_ColliderTree;
	public:
		CPhysicsEngine();
		~CPhysicsEngine();
		void Release();
		bool Initialize();
		bool UpdatePhysics();
		void AddCollider(EColliderType ColliderType,GameObject* Obj);
	};
}

