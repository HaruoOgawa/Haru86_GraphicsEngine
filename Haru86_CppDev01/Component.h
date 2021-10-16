#pragma once

#include "./Object.h"
#include "./Game.h"

class Component
{
public:
	Component(class Object* o);
	~Component();
	virtual void Update();
protected:
	class Object* owner;
	class Game* game;
};

