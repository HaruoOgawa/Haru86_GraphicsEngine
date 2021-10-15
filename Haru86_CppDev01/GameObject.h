#pragma once

#include "./Game.h"
#include "./Object.h"
#include "./VertexArray.h"

#include <vector>
#include <map>
#include <string>

#include <typeinfo>

class GameObject
	: public Object
{
public:
	GameObject(Game* g, PrimitiveType primType);
	GameObject(Game* g, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName);
	~GameObject();
	friend class GameRenderer;
private:
	class MeshRendererComponent* meshComp;
};

