#include "Primitive.h"
#include <glm/glm.hpp>

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
	std::vector<float> v = {
		-0.5f,-0.5f,-0.5f,0.0f,0.0f,-1.0f,0.0f,0.0f,
		-0.5f,0.5f,-0.5f,0.0f,0.0f,-1.0f,0.0f,1.0f,
		0.5f,0.5f,-0.5f,0.0f,0.0f,-1.0f,1.0f,1.0f,
		0.5f,-0.5f,-0.5f,0.0f,0.0f,-1.0f,1.0f,0.0f,
		-0.5f,-0.5f,0.5f,0.0f,0.0f,1.0f,0.0f,0.0f,
		-0.5f,0.5f,0.5f,0.0f,0.0f,1.0f,0.0f,1.0f,
		0.5f,0.5f,0.5f,0.0f,0.0f,1.0f,1.0f,1.0f,
		0.5f,-0.5f,0.5f,0.0f,0.0f,1.0f,1.0f,0.0f,
	};

	std::vector<int> i{
		0,1,2,
		2,3,0,
		4,5,6,
		6,7,4,
		1,5,6,
		6,2,1,
		0,4,7,
		7,3,0,
		3,2,6,
		6,7,3,
		0,1,5,
		5,4,0
	};

	for(auto data : v) {
		vertices->emplace_back(data);
	}

	for(auto data : i) {
		indices->emplace_back(data);
	}
}

void Primitive::CreateSphere(std::vector<float>* vertices, std::vector<int>* indices, float row, float column, float rad ) {
	float pi = 3.14159265f;
	for (auto i = 0; i <= row; i++) {
		auto r = pi / row * i;
		auto ry = glm::cos(r);
		auto rr = glm::sin(r);
		for (auto ii = 0; ii <= column; ii++) {
			float tr = pi * 2 / column * ii;
			float tx = rr * rad * glm::cos(tr);
			float ty = ry * rad;
			float tz = rr * rad * glm::sin(tr);
			float rx = rr * glm::cos(tr);
			float rz = rr * glm::sin(tr);
			
			//pos.push(tx, ty, tz);
			//nor.push(rx, ry, rz);
			//st.push(1 - 1 / column * ii, 1 / row * i);

			vertices->emplace_back(tx);
			vertices->emplace_back(ty);
			vertices->emplace_back(tz);
			vertices->emplace_back(rx);
			vertices->emplace_back(ry);
			vertices->emplace_back(rz);
			vertices->emplace_back(static_cast<float>(1 - 1 / column * ii));
			vertices->emplace_back(static_cast<float>(1 / row * i));
		}
	}
	for (int i = 0; i < row; i++) {
		for (int ii = 0; ii < column; ii++) {
			int r = (column + 1) * i + ii;
			
			//idx.push(r, r + 1, r + column + 2);
		//	idx.push(r, r + column + 2, r + column + 1);

			indices->emplace_back(static_cast<int>(r));
			indices->emplace_back(static_cast<int>(r + 1));
			indices->emplace_back(static_cast<int>(r + column + 2));
			indices->emplace_back(static_cast<int>(r));
			indices->emplace_back(static_cast<int>(r + column + 2));
			indices->emplace_back(static_cast<int>(r + column + 1));
		}
	}
}
