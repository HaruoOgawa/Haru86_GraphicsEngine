#pragma once

#include "../Game/Game.h"
#include "../Component/Component.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <typeinfo>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Object
{
public:
	Object();
	~Object();
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
	class Component* GetComponent(std::string componentName);
	void SetTransform(glm::vec3 pos, glm::quat rot, glm::vec3 s);
	void SetPosition(glm::vec3 pos);
	void SetRotation(glm::quat rot);
	void SetScale(glm::vec3 s);
	virtual void Update();
	glm::vec3 GetPosition();
	glm::quat GetRotation();
	glm::vec3 GetScale();
	class TransformComponent* transform;
	friend class MeshRendererComponent;
	friend class GameRenderer;
	friend class UIComponent;
	friend class RectTransformComponent;
private:
	
	class Game* game;
protected:
	std::unordered_map<std::string, class Component*> myComponent;
};


