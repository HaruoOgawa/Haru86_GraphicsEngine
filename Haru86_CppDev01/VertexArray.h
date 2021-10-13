#pragma once
class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	unsigned int GetNumIndices() { return mNumIndices; }
	void SetActive();
	void UnLoadData();
private:
	void CreateDefaultMesh();
	unsigned int mNumVerts;
	unsigned int mNumIndices;
	unsigned int mVertexBuffer;
	unsigned int mIndexBuffer;
	unsigned int mVertexArray;
};

