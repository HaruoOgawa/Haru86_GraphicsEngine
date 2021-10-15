#include "VertexArray.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "./Primitive.h"
#include <vector>

//default VertexArray
VertexArray::VertexArray() {
	CreateMesh(PrimitiveType::BOARD);
}

VertexArray::VertexArray(PrimitiveType primType) {
	CreateMesh(primType);
}

VertexArray::~VertexArray() {
	UnLoadData();
}

void VertexArray::CreateMesh(PrimitiveType primType) {
	std::vector<float> vertices;
	std::vector<int> indices;

	switch (primType)
	{
	case PrimitiveType::BOARD:
		Primitive::CreateBoard(&vertices, &indices);
		break;
	case PrimitiveType::CUBE:
		Primitive::CreateCube(&vertices, &indices);
		break;
	case PrimitiveType::SPHERE:
		Primitive::CreateSphere(&vertices,&indices);
		break;
	case PrimitiveType::TORUS:
		Primitive::CreateTorus(&vertices,&indices);
		break;
	default:
		Primitive::CreateBoard(&vertices, &indices);
		break;
	}
	
	mNumVerts = vertices.size()/5;
	mNumIndices = indices.size();

	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, mNumVerts * 8 * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNumIndices * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 
		reinterpret_cast<void*>(sizeof(float)*3)
		);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 
		reinterpret_cast<void*>(sizeof(float) * 6)
		);


}

void VertexArray::SetActive() {
	glBindVertexArray(mVertexArray);
}

void VertexArray::UnLoadData() {
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1,&mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}