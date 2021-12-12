#pragma once

#include "../Game/Game.h"
#include "./Object.h"
#include "../Graphics/Mesh.h"

#include <vector>
#include <map>
#include <string>
#include <GL/glew.h>
#include <typeinfo>

enum RenderQueue
{
	Background=1000,
	Geometry=3000,
	Transparent=4000,
	UI=5000
};

enum class RenderType {
	DefaultBuffer,
	FrameBuffer,
	PostProcess
};

class GameObject
	: public Object
{
public:
	GameObject(PrimitiveType primType);
	GameObject(PrimitiveType primType, std::map<GLenum, std::string> shaders);
	GameObject(std::string objPath);
	GameObject(PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName);
	GameObject(PrimitiveType primType, std::string vertexShaderName, std::string tessellationShaderName[2], std::string fragmentShaderName);
	GameObject(PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName,RenderType renderType);
	GameObject(PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName,std::string textureString);
	~GameObject();
	void UseZTest(bool use);
	void SetRenderOlder(int order);
	void ProcessInput(const Uint8* state);
	class MeshRendererComponent* meshComp;
	float animTime = 0.0f;
	friend class GameRenderer;
	friend class TimelineComponent;
	int renderOrder;
private:
	
	RenderType renderType;
};

