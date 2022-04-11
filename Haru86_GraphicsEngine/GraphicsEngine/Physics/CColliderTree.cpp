#include "CColliderTree.h"
#include "GraphicsEngine/Object/GameObject.h"
#include "GraphicsEngine/Graphics/Primitive.h"
#include "CSphereCollider.h"
#include "CBoxCollider.h"
#include "GraphicsEngine/Component/MeshRendererComponent.h"
#include "GraphicsEngine/Component/TransformComponent.h"
#include "../Message/Console.h"

namespace physics {
	CColliderTree::CColliderTree() {

	}

	CColliderTree::~CColliderTree() {

	}

	bool CColliderTree::AddCollider(EColliderType ColliderType, EObjectType ObjectType, GameObject* Obj) {
		const auto& PrimList = Obj->GetComponent<MeshRendererComponent>()->GetMesh()->GetPrimitiveList();
		
		switch (ColliderType)
		{
			case physics::EColliderType::Sphere:
				if (!CreateSphereCollider(PrimList, Obj, ObjectType, ColliderType))return false;
				break;

			case physics::EColliderType::Box:
				if (!CreateSimpleBoxCollider(PrimList, Obj, ObjectType, ColliderType))return false;
				break;

			default:
				break;
		}

		for (auto& Prim :PrimList) {
			Prim->Release();
		}

		return true;
	}

	bool CColliderTree::MakeColliderTree() {
		return true;
	}

	std::vector<std::shared_ptr<ACollider>> CColliderTree::GetPassiveColliderListFromTree(std::shared_ptr<ACollider> Collider) {
		std::vector<std::shared_ptr<ACollider>> PassiveColliderList;
		
		// ひとまず仮の実装(まだツリーを実装していない)
		for (const auto& PassiveCollider : m_ColliderList) {
			if (Collider!=PassiveCollider) {
				PassiveColliderList.push_back(PassiveCollider);
			}
		}

		return PassiveColliderList;
	}

	const std::vector<std::shared_ptr<ACollider>>& CColliderTree::GetColliderList()const {
		return m_ColliderList;
	}

	bool CColliderTree::CreateSphereCollider(const std::vector<std::shared_ptr<Primitive>>& PrimitiveList, GameObject* Obj, EObjectType ObjectType, EColliderType ColliderType) {
		glm::vec3 CenterPos;
		float Radius = 0.0f;

		for (auto& Prim : PrimitiveList) {
			glm::vec3 MaxCenterPos;
			float MaxRadius;
			if (!CalculateSphereVolumeFromAABB(Prim->GetVertices()[0], MaxCenterPos, MaxRadius))return false;

			if (MaxRadius > Radius) {
				CenterPos = MaxCenterPos;
				Radius = MaxRadius;
			}
		}

		m_ColliderList.push_back(std::make_shared<CSphereCollider>(ObjectType, Obj->GetComponent<TransformComponent>(), CenterPos, Radius));

		return true;
	}

	bool CColliderTree::CreateSimpleBoxCollider(const std::vector<std::shared_ptr<Primitive>>& PrimitiveList, GameObject* Obj, EObjectType ObjectType, EColliderType ColliderType) {
		
		glm::vec3 CenterPos = glm::vec3(0.0f, 0.0f, 0.0f);
		
		std::vector<glm::vec3> LocalAxis;
		LocalAxis.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		LocalAxis.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		LocalAxis.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

		glm::vec3 LocalAxisSize = Obj->GetComponent<TransformComponent>()->GetScale()*0.5f;

		m_ColliderList.push_back(std::make_shared<CBoxCollider>(ObjectType, Obj->GetComponent<TransformComponent>(), CenterPos, LocalAxis, LocalAxisSize));

		return true;
	}

	bool CColliderTree::CreateBoxCollider(const std::vector<std::shared_ptr<Primitive>>& PrimitiveList, GameObject* Obj, EObjectType ObjectType, EColliderType ColliderType) {
		return true;
	}

	bool CColliderTree::CalculateAABB(const std::vector<float>& Vertices, glm::vec3& CenterPos, glm::vec3& MaxPos, glm::vec3& MinPos) {
		int MinX = 0, MaxX = 0, MinY = 0, MaxY = 0, MinZ = 0, MaxZ = 0;

		for (int i = 0; i < static_cast<int>(Vertices.size());i+=3) {
			if (Vertices[i + 0] < Vertices[MinX + 0])MinX = i;
			if (Vertices[i + 0] > Vertices[MaxX + 0])MaxX = i;

			if (Vertices[i + 1] < Vertices[MinY + 1])MinY = i;
			if (Vertices[i + 1] > Vertices[MaxY + 1])MaxY = i;

			if (Vertices[i + 2] < Vertices[MinZ + 2])MinZ = i;
			if (Vertices[i + 2] > Vertices[MaxZ + 2])MaxZ = i;
		}

		float MinDist = 0.0f, MaxDist = 0.0f;

		glm::vec3 xvec = glm::vec3(Vertices[MaxX + 0], Vertices[MaxX + 1], Vertices[MaxX + 2]) - glm::vec3(Vertices[MinX + 0], Vertices[MinX + 1], Vertices[MinX + 2]);
		float distx = glm::dot(xvec, xvec);

		glm::vec3 yvec = glm::vec3(Vertices[MaxY + 0], Vertices[MaxY + 1], Vertices[MaxY + 2]) - glm::vec3(Vertices[MinY + 0], Vertices[MinY + 1], Vertices[MinY + 2]);
		float disty = glm::dot(yvec, yvec);

		glm::vec3 zvec = glm::vec3(Vertices[MaxZ + 0], Vertices[MaxZ + 1], Vertices[MaxZ + 2]) - glm::vec3(Vertices[MinZ + 0], Vertices[MinZ + 1], Vertices[MinZ + 2]);
		float distz = glm::dot(zvec, zvec);

		// 一番離れたペアを選択する
		MaxPos = glm::vec3(Vertices[MaxX + 0], Vertices[MaxX + 1], Vertices[MaxX + 2]);
		MinPos = glm::vec3(Vertices[MinX + 0], Vertices[MinX + 1], Vertices[MinX + 2]);

		if (disty > distx && disty > distz) {
			MaxPos = glm::vec3(Vertices[MaxY + 0], Vertices[MaxY + 1], Vertices[MaxY + 2]);
			MinPos = glm::vec3(Vertices[MinY + 0], Vertices[MinY + 1], Vertices[MinY + 2]);
		}
		else if (distz > distx && distz > disty) {
			MaxPos = glm::vec3(Vertices[MaxZ + 0], Vertices[MaxZ + 1], Vertices[MaxZ + 2]);
			MinPos = glm::vec3(Vertices[MinZ + 0], Vertices[MinZ + 1], Vertices[MinZ + 2]);
		}

		CenterPos = (MaxPos + MinPos) * 0.5f;

		return true;
	}

	bool CColliderTree::CalculateSphereVolumeFromAABB(const std::vector<float>& Vertices, glm::vec3& CenterPos, float& Radius) {
		glm::vec3 MaxPos, MinPos;

		if (!CalculateAABB(Vertices,CenterPos,MaxPos,MinPos))return false;

		// 半径を計算
		Radius = glm::sqrt(glm::dot(MaxPos-CenterPos, MaxPos - CenterPos));

		return true;
	}

	bool CColliderTree::OptimizeSphereVolume() {
		return true;
	}

	bool CColliderTree::CalculateOBB() {
		return true;
	}

	bool CColliderTree::OptimizeOBB() {
		return true;
	}

}