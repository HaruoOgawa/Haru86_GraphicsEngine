#include "Graphics.h"
#include "./Mesh.h"
#include <iostream>
#include "./ComputeShader.h"
#include "GraphicsEngine/Graphics/Primitive.h"
#include <GL/glew.h>
#include <GL/glut.h>

void Graphics::DrawInstancedWithMesh(Mesh* mesh, int count) {
	for (int i = 0; i < mesh->m_primitives.size();i++) {
		mesh->m_primitives[i]->SetActive();
		printf("mesh->m_primitives[i]->GetNumIndices():%d \n", mesh->m_primitives[i]->GetNumIndices());
		glDrawElementsInstanced(GL_TRIANGLES, mesh->m_primitives[i]->GetNumIndices(), GL_UNSIGNED_SHORT, nullptr, count);
	}
}
