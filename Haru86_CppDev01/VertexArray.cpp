#include "VertexArray.h"
#include <GL/glew.h>

//default VertexArray
VertexArray::VertexArray() {
	CreateDefaultMesh();
}

VertexArray::~VertexArray() {
	UnLoadData();
}

void VertexArray::CreateDefaultMesh() {
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mNumVerts = 4;
	mNumIndices = 6;

	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, mNumVerts * 8 * sizeof(float), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNumIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

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