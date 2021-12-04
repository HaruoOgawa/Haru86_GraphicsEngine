#include "Graphics.h"
#include "./Mesh.h"
#include <iostream>
#include "./ComputeShader.h"
#include "GraphicsEngine/Graphics/Primitive.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "GraphicsEngine/Graphics/Material.h"

void Graphics::DrawInstancedWithMesh(Mesh* mesh, int count, Material* material) {
	for (int i = 0; i < mesh->m_primitives.size();i++) {
		mesh->m_primitives[i]->SetActive();
		glDrawElementsInstanced(GL_TRIANGLES, mesh->m_primitives[i]->GetNumIndices(), GL_UNSIGNED_SHORT, nullptr, count);
	}
}
