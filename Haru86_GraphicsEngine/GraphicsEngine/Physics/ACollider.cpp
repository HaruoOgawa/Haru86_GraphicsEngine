#include "ACollider.h"

namespace physics {
	ACollider::ACollider(EObjectType ObjectType, TransformComponent* Transform) :
		m_ObjectType(ObjectType),
		m_Transform(Transform),
		m_Force(glm::vec3(0.0f)),
		m_Mass(1.0f)
	{
	}

	ACollider::~ACollider() {

	}

	EObjectType ACollider::GetObjectType()const {
		return m_ObjectType;
	}

	bool ACollider::DetectCollider() {
		return true;
	}

	void ACollider::SetForce(glm::vec3 Force) {
		m_Force = Force;
	}

	const glm::vec3& ACollider::GetForce()const {
		return m_Force;
	}

	void ACollider::SetMass(float Mass) {
		m_Mass = Mass;
	}

	float ACollider::GetMass()const {
		return m_Mass;
	}

	TransformComponent* ACollider::GetTransform() {
		return m_Transform;
	}
}
