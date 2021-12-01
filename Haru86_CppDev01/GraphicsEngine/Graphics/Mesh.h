#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

enum class PrimitiveType {
	BOARD,
	CUBE,
	SPHERE
};

class Mesh
{
public:
	Mesh();
	Mesh(PrimitiveType primType);
	~Mesh();
	void UnLoadData();
	void Draw();
	friend class Graphics;
	friend class glTFLoader;
	glm::mat4 localMatrix;
	
private:
	void CreateMesh(PrimitiveType primType);
	std::vector<std::unique_ptr<class Primitive>> m_primitives;
};

