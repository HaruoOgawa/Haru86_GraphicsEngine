#pragma once
#include <vector>

class Primitive
{
public:
	Primitive(std::vector<float> vertices, std::vector<int> indices);
	Primitive(std::vector<std::vector<float>> vertices, std::vector<int> dimention, std::vector<unsigned short> indices);
	~Primitive();
	unsigned int GetNumIndices() { return mNumIndices; }
	int GetVertNum() { return vertNum; }
	void CreatePrimitive(std::vector<float> vertices, std::vector<int> indices);
	void CreatePrimitive(std::vector<std::vector<float>> vertices,std::vector<int> dimention, std::vector<unsigned short> indices);
	void Draw();
	void SetActive();
	void UnLoadData();

	static void CreateBoard(std::vector<float>* vertices,std::vector<int>* indices);
	static void CreateBoard(std::vector<std::vector<float>>* vertices, std::vector<int>* dimention, std::vector<unsigned short>* indices);
	static void CreateCube(std::vector<float>* vertices, std::vector<int>* indices);
	static void CreateSphere(std::vector<float>* vertices, std::vector<int>* indices, float row = 16.0f, float column=16.0f,float rad=1.0f);
private:
	unsigned int mNumIndices;
	unsigned int mVertexArray;
	int vertNum;
};

