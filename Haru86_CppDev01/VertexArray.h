#pragma once
class VertexArray
{
public:
	VertexArray();
	~VertexArray();
private:
	void CreateDefaultMesh();
	unsigned int mNumVerts;
	unsigned int mNumIndices;
	unsigned int mVertexBuffer;
	unsigned int mIndexBuffer;
	unsigned int mVertexArray;
};

