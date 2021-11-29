#include "Mesh.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "./Primitive.h"
#include <vector>

//default Mesh
Mesh::Mesh() {

}

Mesh::Mesh(PrimitiveType primType) {
	CreateMesh(primType);
	printf("Create Mesh ptr: %p \n", this);
}

Mesh::~Mesh() {
	UnLoadData();
}

void Mesh::CreateMesh(PrimitiveType primType) {
	std::vector<float> vertices;
	std::vector<int> indices;

	std::vector<std::vector<float>> vertices2D;
	std::vector<int> dimention;
	std::vector<int> indices2D;

	switch (primType)
	{
	case PrimitiveType::BOARD:
		//Primitive::CreateBoard(&vertices, &indices);
		Primitive::CreateBoard(&vertices2D, &dimention,&indices2D);
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
	
	//std::unique_ptr<Primitive> prim = std::make_unique<Primitive>(vertices,indices);
	std::unique_ptr<Primitive> prim = std::make_unique<Primitive>(vertices2D, dimention, indices2D);
	m_primitives.push_back(std::move(prim));

}

void Mesh::Draw() {
	for (int i = 0; i < m_primitives.size();i++) {
		m_primitives[i]->Draw();
	}

	printf("m_primitives.size() (%p):%d \n",this,static_cast<int>(m_primitives.size()));
}

void Mesh::UnLoadData() {
	
}