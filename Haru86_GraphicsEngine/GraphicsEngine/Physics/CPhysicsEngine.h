#pragma once
#include <vector>
#include <memory>

namespace physics {
	class CColliderTree;
	class ICollider;

	class CPhysicsEngine
	{
		std::unique_ptr<CColliderTree> m_ColliderTree;
	public:
		CPhysicsEngine();
		~CPhysicsEngine();
		bool Initialize();
		bool UpdatePhysics();
	};
}

