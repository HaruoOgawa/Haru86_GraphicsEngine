#pragma once
#include <vector>
#include <memory>
#include "EColliderType.h"
class GameObject;

namespace physics {
	class ACollider;

	class CColliderTree
	{
		std::vector<std::shared_ptr<ACollider>> m_ColliderList;
	public:
		CColliderTree();
		virtual ~CColliderTree();
		void AddCollider(EColliderType ColliderType, GameObject* Obj);
	};
}



