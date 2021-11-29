#include "Graphics.h"
#include "./Mesh.h"
#include <iostream>
#include "./ComputeShader.h"
#include "GraphicsEngine/Graphics/Primitive.h"

void Graphics::DrawInstancedWithMesh(Mesh* mesh, int count) {
	for (int i = 0; i < mesh->m_primitives.size();i++) {
		mesh->m_primitives[i]->SetActive();
		glDrawElementsInstanced(GL_TRIANGLES, mesh->m_primitives[i]->GetNumIndices(), GL_UNSIGNED_INT, nullptr, count);
	}
	printf("m_primitives.size() (%p):%d \n", mesh, static_cast<int>(mesh->m_primitives.size()));
}
