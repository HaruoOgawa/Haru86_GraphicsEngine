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
	GameObject(PrimitiveType primType);
	GameObject(PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName);
	~GameObject();
	void UseZTest(bool use);
	void SetRenderOlder(int order);
	friend class GameRenderer;
	int renderOrder;
private:
	class MeshRendererComponent* meshComp;
};

