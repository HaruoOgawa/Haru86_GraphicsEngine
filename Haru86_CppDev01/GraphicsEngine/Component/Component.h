#pragma once

#include "../Object/Object.h"
#include "../Game/Game.h"
#include <string>
#include <memory>

class Component
{
public:
	Component(class Object* o,std::string name);
	virtual ~Component();
	virtual void Start();
	virtual void Update();
	virtual void ProcessInput(const Uint8* state)const = 0;
	std::string superClassName;
	friend Object;
protected:
	class Object* owner;
	class Game* game;
	
};

