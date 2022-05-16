#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>

class Component;
class TransformComponent;

namespace obj {
	class Node
	{
		std::vector<std::shared_ptr<Node>> m_Nodes;
		std::shared_ptr<TransformComponent> m_transform;
		std::unordered_map<std::type_index, std::shared_ptr<Component>> m_ComponentList;
	public:
		//
		Node();
		~Node();

		//
		const std::shared_ptr<TransformComponent>& GetTransform()const;
		void AddNode(const std::shared_ptr<Node>& node);
		const std::vector<std::shared_ptr<Node>>& GetNodeList()const;
		const std::shared_ptr<Node>& GetNode(int index)const;

		//
		template<typename T>
		void AddComponent(std::shared_ptr<Component> component) {
			m_ComponentList.insert({ typeid(T),component });
		}

		template<typename T>
		void RemoveComponent() {
			auto item = m_ComponentList.find(typeid(T));
			m_ComponentList.erase(item->first);
		}

		template<typename T>
		T* GetComponent()const {
			auto item = m_ComponentList.find(typeid(T));
			return static_cast<T*>(item->second.get());
		}
	private:
	};
}
