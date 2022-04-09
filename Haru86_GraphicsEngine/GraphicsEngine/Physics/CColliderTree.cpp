#include "CColliderTree.h"
#include "GraphicsEngine/Object/GameObject.h"

namespace physics {
	CColliderTree::CColliderTree() {

	}

	CColliderTree::~CColliderTree() {

	}

	void CColliderTree::AddCollider(EColliderType ColliderType, GameObject* Obj) {
		switch (ColliderType)
		{
			case physics::EColliderType::Sphere:
				break;

			case physics::EColliderType::Box:
				break;

			default:
				break;
		}
	}
}