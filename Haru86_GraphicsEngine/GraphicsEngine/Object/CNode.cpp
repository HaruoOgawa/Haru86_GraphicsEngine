#include "CNode.h"
#include "GraphicsEngine/Component/Component.h"
#include "GraphicsEngine/Component/TransformComponent.h"

namespace obj {
	CNode::CNode() {
		m_transform = std::make_shared<TransformComponent>(nullptr, glm::vec3(0, 0, 0), glm::quat(glm::vec3(0, 0, 0)), glm::vec3(1.0f, 1.0f, 1.0f));
		AddComponent<TransformComponent>(m_transform);
	}

	CNode::~CNode() {

	}

	const std::shared_ptr<TransformComponent>& CNode::GetTransform()const {
		return m_transform;
	}

	void CNode::AddNode(const std::shared_ptr<CNode>& node) {
		m_Nodes.push_back(node);
	}

	const std::vector<std::shared_ptr<CNode>>& CNode::GetNodeList()const {
		return m_Nodes;
	}

	const std::shared_ptr<CNode>& CNode::GetNode(int index)const {
		return m_Nodes[index];
	}
}