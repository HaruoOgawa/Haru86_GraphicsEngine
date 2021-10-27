#pragma once

#include "./Game.h"
#include "./Object.h"
#include "./VertexArray.h"

#include <vector>
#include <map>
#include <string>

#include <typeinfo>

enum RenderQueue
{
	Background=1000,
	Geometry=3000,
	Transparent=4000,
	UI=5000
};

enum class RenderType {
	FrameBuffer,
	DefaultBuffer,
	Test,
	Obj
};

class GameObject
	: public Object
{
public:
	GameObject(PrimitiveType primType);
	GameObject(PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName);
	GameObject(PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName,RenderType renderType);
	~GameObject();
	void UseZTest(bool use);
	void SetRenderOlder(int order);
	void ProcessInput(const Uint8* state);
	class MeshRendererComponent* meshComp;
	friend class GameRenderer;
	friend class TimelineComponent;
	int renderOrder;
private:
	
	RenderType dummy;
};

