#include "Mesh.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "./Primitive.h"
#include <vector>

//default Mesh
Mesh::Mesh() {
	CreateMesh(PrimitiveType::BOARD);
}

Mesh::Mesh(PrimitiveType primType) {
	CreateMesh(primType);
}

Mesh::~Mesh() {
	UnLoadData();
}

void Mesh::CreateMesh(PrimitiveType primType) {
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
	default:
		Primitive::CreateBoard(&vertices, &indices);
		break;
	}
	
	std::unique_ptr<Primitive> prim = std::make_unique<Primitive>(vertices,indices);
	m_primitives.push_back(std::move(prim));

}

void Mesh::Draw() {
	for (int i = 0; i < m_primitives.size();i++) {
		m_primitives[i]->Draw();
	}
}

void Mesh::UnLoadData() {
	
}