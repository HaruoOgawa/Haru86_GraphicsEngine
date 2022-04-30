#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

enum class PrimitiveType {
	BOARD,
	CUBE,
	SPHERE,
	POINT,
	CUSTOM,
};

enum class GLDrawType {
	NONE,
	TESSELLATION
};

class Primitive;

class Mesh
{
public:
	Mesh();
	Mesh(PrimitiveType primType);
	~Mesh();
	void UnLoadData();
	void Draw();
	void Draw(GLDrawType drawType);

	const std::vector<std::shared_ptr<Primitive>>& GetPrimitiveList()const;

	friend class Graphics;
	friend class glTFLoader;
	glm::mat4 localMatrix;
	GLDrawType glDrawType;
private:
	void CreateMesh(PrimitiveType primType);
	std::vector<std::shared_ptr<Primitive>> m_primitives;
};

