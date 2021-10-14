#pragma once

#include "./Game.h"
#include "./Object.h"
//#include "./MeshRendererComponent.h"

#include <vector>
#include <map>
#include <string>

#include <typeinfo>

class GameObject
	: public Object
{
public:
	GameObject(Game* g, std::string vertexShaderName, std::string fragmentShaderName);
	~GameObject();
	class MeshRendererComponent* meshComp;
private:
	
};

