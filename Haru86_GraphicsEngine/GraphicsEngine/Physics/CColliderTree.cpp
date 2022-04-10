#include "CColliderTree.h"
#include "GraphicsEngine/Object/GameObject.h"
#include "CSphereCollider.h"
#include "CBoxCollider.h"
#include "GraphicsEngine/Component/MeshRendererComponent.h"
#include "GraphicsEngine/Component/TransformComponent.h"
#include "../Debug/Console.h"

namespace physics {
	CColliderTree::CColliderTree() {

	}

	CColliderTree::~CColliderTree() {

	}

	bool CColliderTree::AddCollider(EColliderType ColliderType, GameObject* Obj) {
		const auto& PrimList = Obj->GetComponent<MeshRendererComponent>()->GetMesh()->GetPrimitiveList();
		//PrimList[0]->GetVertices()
		
		switch (ColliderType)
		{
			case physics::EColliderType::Sphere:
				
				//m_ColliderList.push_back(std::make_shared<CSphereCollider>(ColliderType, Obj->GetComponent<TransformComponent>()));
				break;

			case physics::EColliderType::Box:
				//m_ColliderList.push_back(std::make_shared<CBoxCollider>());
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

	bool CColliderTree::CalculateSphereVolumeFromAABB() {
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