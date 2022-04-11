#pragma once
#include <vector>
#include <memory>
#include "EColliderType.h"
#include "EObjectType.h"

class GameObject;

namespace physics {
	class CColliderTree;
	class ACollider;

	class CPhysicsEngine
	{
		std::unique_ptr<CColliderTree> m_ColliderTree;
		std::vector<std::shared_ptr<ACollider>> m_DynamicColliderList;

	public:
		CPhysicsEngine();
		~CPhysicsEngine();
		void Release();
		bool Initialize();
		bool UpdatePhysics();
		void AddCollider(EColliderType ColliderType,EObjectType ObjectType,GameObject* Obj);
	private:
		bool AddForce(std::shared_ptr<ACollider> Collider);
		bool UpdatePosition(std::shared_ptr<ACollider> Collider);
	};
}

