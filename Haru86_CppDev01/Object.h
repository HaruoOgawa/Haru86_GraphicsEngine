#pragma once

#include "./Game.h"
#include "./Component.h"
#include <vector>
#include <map>
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
	//class Component* GetComponent(std::string componentName);
	void SetTransform(glm::vec3 pos, glm::quat rot, glm::vec3 s);
	void SetPosition(glm::vec3 pos);
	void SetRotation(glm::quat rot);
	void SetScale(glm::vec3 s);
	glm::vec3 GetPosition();
	glm::quat GetRotation();
	glm::vec3 GetScale();
	//void GetTransform(glm::vec3& pos, glm::quat& rot, glm::vec3& s) { pos = transform->position; rot = transform->rotation; s = transform->scale; }
	friend class MeshRendererComponent;
	friend class GameRenderer;
private:
	class TransformComponent* transform;
	class Game* game;
protected:
	//std::map<std::string, class Component*> myComponent;
	std::vector<class Component*> myComponent;
};


