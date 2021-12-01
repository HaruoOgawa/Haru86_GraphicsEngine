#pragma once
#include <vector>

class glTFBinaryReader
{
public:
	glTFBinaryReader();
	~glTFBinaryReader();
	std::vector<float> vertex;
	std::vector<unsigned char> subDataVertex;
	std::vector<float> normal;
	std::vector<unsigned char> subDataNormal;
	std::vector<float> texcoord;
	std::vector<unsigned char> subDataTexcoord;

	std::vector<unsigned short> indices;
	std::vector<unsigned char> subDataIndices;
};

