#pragma once

#include "../Object/Object.h"
#include "../Game/Game.h"
#include <string>
#include <memory>

class Component
{
public:
	Component(std::shared_ptr<class Object> o,std::string name);
	~Component();
	virtual void Start();
	virtual void Update();
	virtual void ProcessInput(const Uint8* state)const = 0;
	std::string superClassName;
	friend Object;
protected:
	std::shared_ptr<class Object> owner;
	std::shared_ptr<class Game> game;
	
};

