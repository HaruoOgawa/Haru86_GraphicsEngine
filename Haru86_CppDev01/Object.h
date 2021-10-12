#pragma once

#include "./Game.h"
#include "./Component.h"
#include <vector>
#include <map>
#include <string>
#include <typeinfo>

class Object
{
public:
	Object(Game* g);
	~Object();
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
	//class Component* GetComponent();
private:
	class Game* game;
	std::map<std::string, class Component*> myComponent;
};


