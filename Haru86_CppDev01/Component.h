#pragma once

#include "./Object.h"
#include "./Game.h"

class Component
{
public:
	Component(class Object* o);
	~Component();
	virtual void Update();
	virtual void ProcessInput(const Uint8* state)const = 0;
protected:
	class Object* owner;
	class Game* game;
};

