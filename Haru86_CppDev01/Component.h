#pragma once

#include "./GameObject.h"

class Component
{
public:
	Component(class GameObject* o);
	~Component();
	virtual void Update();
private:
	class GameObject* owner;
};

