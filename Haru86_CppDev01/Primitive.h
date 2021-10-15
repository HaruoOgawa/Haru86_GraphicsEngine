#pragma once
#include <vector>

class Primitive
{
public:
	static void CreateBoard(std::vector<float>* vertices,std::vector<int>* indices);
	static void CreateCube(std::vector<float>* vertices, std::vector<int>* indices);
	static void CreateSphere(std::vector<float>* vertices, std::vector<int>* indices, float row = 16.0f, float column=16.0f,float rad=1.0f);
};

