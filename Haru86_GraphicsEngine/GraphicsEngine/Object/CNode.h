#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <SDL.h>

class Component;
class TransformComponent;

namespace obj {
	class CNode
	{
		std::vector<std::shared_ptr<CNode>> m_Nodes;
		std::shared_ptr<TransformComponent> m_transform;
		std::unordered_map<std::type_index, std::shared_ptr<Component>> m_ComponentList;
	public:
		//
		CNode();
		~CNode();

		//
		bool Update();
		bool Draw();
		void ProcessInput(const SDL_Event& e);

		//
		const std::unordered_map<std::type_index, std::shared_ptr<Component>>& GetComponentList()const;

		const std::shared_ptr<TransformComponent>& GetTransform()const;
		std::shared_ptr<TransformComponent>& GetTransform();

		void AddNode(const std::shared_ptr<CNode>& node);
		const std::vector<std::shared_ptr<CNode>>& GetNodeList()const;
		const std::shared_ptr<CNode>& GetNode(int index)const;

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
