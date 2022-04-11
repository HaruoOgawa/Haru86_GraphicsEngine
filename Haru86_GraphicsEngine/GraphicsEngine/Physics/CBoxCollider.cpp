#include "CBoxCollider.h"
#include "GraphicsEngine/Component/TransformComponent.h"

namespace physics {
	CBoxCollider::CBoxCollider(EObjectType ObjectType, TransformComponent* Transform,
		glm::vec3 CenterPos, std::vector<glm::vec3> LocalAxis, glm::vec3 LocalAxisSize) 
		: ACollider(ObjectType,EColliderType::Box, Transform),
		m_CenterPos(CenterPos),
		m_LocalAxis(LocalAxis),
		m_LocalAxisSize(LocalAxisSize)
	{
	}

	CBoxCollider::~CBoxCollider() {

	}

	std::shared_ptr<SCollisionInfo> CBoxCollider::DetectBoxCollider(std::shared_ptr<ACollider> Collider) {
		std::shared_ptr<SCollisionInfo> CollisionInfo = nullptr;

		return CollisionInfo;
	}

	std::shared_ptr<SCollisionInfo> CBoxCollider::DetectSphereCollider(std::shared_ptr<ACollider> Collider) {
		std::shared_ptr<SCollisionInfo> CollisionInfo = nullptr;

		return CollisionInfo;
	}

}