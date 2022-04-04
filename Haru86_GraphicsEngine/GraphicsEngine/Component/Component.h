#pragma once

#include "../Object/Object.h"
#include "../Game/Game.h"
#include <string>
#include <memory>

class Component
{
public:
	Component(class Object* o);
	virtual ~Component();
	virtual void Start();
	virtual void Update();
	virtual void Dtaw();
	virtual void ProcessInput(const Uint8* state) = 0;
	friend Object;
protected:
	class Object* owner;
	class Game* game;
	
};

