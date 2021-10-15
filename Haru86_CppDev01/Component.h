#pragma once

#include "./Object.h"
#include "./Game.h"

class Component
{
public:
	Component(class Game* g,class Object* o);
	~Component();
	virtual void Update();
protected:
	class Object* owner;
	class Game* game;
};

