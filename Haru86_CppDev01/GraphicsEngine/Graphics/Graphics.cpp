#include "Graphics.h"
#include "./Mesh.h"
#include <iostream>
#include "./ComputeShader.h"

void Graphics::DrawInstancedWithMesh(Mesh* mesh, int count) {
	mesh->SetActive();
	glDrawElementsInstanced(GL_TRIANGLES, mesh->GetNumIndices(), GL_UNSIGNED_INT, nullptr, count);
}

void Graphics::Dispatch(ComputeShader cs, int xGroupNum, int yGroupNum, int zGroupNum) {

}