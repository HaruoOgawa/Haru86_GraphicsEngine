#pragma once

#include "../Game/Game.h"
#include "../Component/Component.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <typeinfo>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <memory>
#include <typeindex>

class Component;

class Object
{
public:
	Object();
	virtual ~Object();

	template<typename T>
	void AddComponent(std::shared_ptr<Component> component) {
		myComponent.insert({ typeid(T),component });
	}

	void RemoveComponent(std::shared_ptr<Component> component);
	//Component* GetComponent(std::string componentName);
	
	template<typename T>
	const std::shared_ptr<Component>& GetComponent()const {
		auto item = myComponent.find(typeid(T));
		return item->second;
	}

	void SetTransform(glm::vec3 pos, glm::quat rot, glm::vec3 s);
	void SetPosition(glm::vec3 pos);
	void SetRotation(glm::quat rot);
	void SetScale(glm::vec3 s);
	virtual void Update();
	glm::vec3 GetPosition();
	glm::quat GetRotation();
	glm::vec3 GetScale();
	std::shared_ptr<class TransformComponent> transform;
	friend class MeshRendererComponent;
	friend class GraphicsRenderer;
	friend class UIComponent;
	friend class RectTransformComponent;
private:
	class Game* game;
protected:
	std::unordered_map<std::type_index, std::shared_ptr<Component>> myComponent;
};


