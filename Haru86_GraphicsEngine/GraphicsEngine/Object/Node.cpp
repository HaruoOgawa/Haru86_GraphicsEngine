#include "Node.h"
#include "GraphicsEngine/Component/Component.h"
#include "GraphicsEngine/Component/TransformComponent.h"

namespace obj {
	Node::Node() {
		m_transform = std::make_shared<TransformComponent>(nullptr, glm::vec3(0, 0, 0), glm::quat(glm::vec3(0, 0, 0)), glm::vec3(1.0f, 1.0f, 1.0f));
		AddComponent<TransformComponent>(m_transform);
	}

	Node::~Node() {

	}

	const std::shared_ptr<TransformComponent>& Node::GetTransform()const {
		return m_transform;
	}

	void Node::AddNode(const std::shared_ptr<Node>& node) {
		m_Nodes.push_back(node);
	}

	const std::vector<std::shared_ptr<Node>>& Node::GetNodeList()const {
		return m_Nodes;
	}

	const std::shared_ptr<Node>& Node::GetNode(int index)const {
		return m_Nodes[index];
	}
}