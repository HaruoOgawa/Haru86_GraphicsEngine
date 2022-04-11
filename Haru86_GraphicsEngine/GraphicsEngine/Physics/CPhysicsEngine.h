#pragma once
#include <vector>
#include <memory>
#include "EColliderType.h"
#include "EObjectType.h"

class GameObject;

namespace physics {
	class CColliderTree;
	class ACollider;
	struct SCollisionInfo;

	class CPhysicsEngine
	{
		std::unique_ptr<CColliderTree> m_ColliderTree;
		std::vector<std::shared_ptr<ACollider>> m_DynamicColliderList;
		std::vector<std::shared_ptr<SCollisionInfo>> m_CollisionInfoList;

	public:
		CPhysicsEngine();
		~CPhysicsEngine();
		void Release();
		void ReleaseLoopResource();
		bool Initialize();
		bool UpdatePhysics();
		void AddCollider(EColliderType ColliderType,EObjectType ObjectType,GameObject* Obj);
	private:
		bool AddForce(std::shared_ptr<ACollider> Collider);
		bool DetectCollider(std::shared_ptr<ACollider> Collider);
		bool UpdatePosition(std::shared_ptr<ACollider> Collider);
	};
}

