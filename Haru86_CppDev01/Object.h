#pragma once

#include "./Game.h"
#include "./Component.h"
#include <vector>
#include <map>
#include <string>
#include <typeinfo>
#include <glm/glm.hpp>

class Object
{
public:
	Object(class Game* g);
	~Object();
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
	class Component* GetComponent(std::string componentName);
	friend class MeshRendererComponent;
	friend class GameRenderer;
private:
	class TransformComponent* transform;
	class Game* game;
	std::map<std::string, class Component*> myComponent;
	
};


