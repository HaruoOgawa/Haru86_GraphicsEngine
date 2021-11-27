#pragma once
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
	unsigned int GetNumIndices() { return mNumIndices; }
	void SetActive();
	void UnLoadData();
private:
	void CreateMesh(PrimitiveType primType);
	unsigned int mNumVerts;
	unsigned int mNumIndices;
	unsigned int mVertexBuffer;
	unsigned int mIndexBuffer;
	unsigned int mVertexArray;
};

