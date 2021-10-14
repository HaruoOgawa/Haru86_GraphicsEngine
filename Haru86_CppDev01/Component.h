#pragma once

#include "./Object.h"

class Component
{
public:
	Component(class Object* o);
	~Component();
	virtual void Update();
protected:
	class Object* owner;
};

