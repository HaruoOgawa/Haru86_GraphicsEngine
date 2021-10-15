#include "Primitive.h"

void Primitive::CreateBoard(std::vector<float>* vertices, std::vector<int>* indices) {
	std::vector<float> v= {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
	};
	std::vector<int> i= {
		0, 1, 2,
		2, 3, 0
	};

	for (auto data : v) {
		vertices->emplace_back(data);
	}

	for (auto data : i) {
		indices->emplace_back(data);
	}
}

void Primitive::CreateCube(std::vector<float>* vertices, std::vector<int>* indices) {

}

void Primitive::CreateSphere(std::vector<float>* vertices, std::vector<int>* indices) {

}
void Primitive::CreateTorus(std::vector<float>* vertices, std::vector<int>* indices) {

}