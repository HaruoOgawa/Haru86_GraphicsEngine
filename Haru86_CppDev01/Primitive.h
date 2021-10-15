#pragma once
#include <vector>

class Primitive
{
public:
	static void CreateBoard(std::vector<float>* vertices,std::vector<int>* indices);
	static void CreateCube(std::vector<float>* vertices, std::vector<int>* indices);
	static void CreateSphere(std::vector<float>* vertices, std::vector<int>* indices);
	static void CreateTorus(std::vector<float>* vertices, std::vector<int>* indices);
};

