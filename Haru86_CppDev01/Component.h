#pragma once

#include "./Object.h"

class Component
{
public:
	Component(class Object* o);
	~Component();
	virtual void Update();
private:
	class Object* owner;
};

