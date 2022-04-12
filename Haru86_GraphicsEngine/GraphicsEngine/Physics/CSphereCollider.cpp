#include "CSphereCollider.h"

namespace physics {
	CSphereCollider::CSphereCollider(EObjectType ObjectType, TransformComponent* Transform, glm::vec3 CenterPos, float Radius)
		: ACollider(ObjectType,EColliderType::Sphere, Transform),
		m_CenterPos(CenterPos),
		m_Radius(Radius)
	{
	}
	
	CSphereCollider::~CSphereCollider() {

	}

	std::shared_ptr<SCollisionInfo> CSphereCollider::DetectBoxCollider(std::shared_ptr<ACollider> Collider) {
		std::shared_ptr<SCollisionInfo> CollisionInfo = nullptr;

		return CollisionInfo;
	}
	
	std::shared_ptr<SCollisionInfo> CSphereCollider::DetectSphereCollider(std::shared_ptr<ACollider> Collider) {
		std::shared_ptr<SCollisionInfo> CollisionInfo = nullptr;

		return CollisionInfo;
	}

	bool CSphereCollider::CalcIsingCollided(glm::vec3& CollidedNormal, float& CollidedDepth) {
		CollidedNormal = CollidedNormal + glm::abs(glm::normalize(CollidedNormal)) * m_Radius;
		CollidedDepth = glm::dot(CollidedNormal, CollidedNormal);

		return (CollidedDepth < m_Radius* m_Radius);
	}
}