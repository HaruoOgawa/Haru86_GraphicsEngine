#include "MeshRendererComponent.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "./TransformComponent.h"

#include <iostream>

MeshRendererComponent::MeshRendererComponent(Object* o, std::string vertexShaderName, std::string fragmentShaderName)
	: Component(o),myowner(o)
{
	mesh =new VertexArray();
	material = new Material(vertexShaderName,fragmentShaderName);
}

MeshRendererComponent::~MeshRendererComponent() {
	delete mesh;
	delete material;
}

void MeshRendererComponent::Update() {

}

void MeshRendererComponent::Draw() {
	material->SetActive();
	material->SetMatrixUniform("MVPMatrix", owner->transform->GetMVPMatrix());
	
	/*glm::mat4 testMat = owner->transform->GetMVPMatrix();
	printf("MVPMatrix_____________________________________________________ \n");
	for (int i = 0; i < 4; i++) {
		printf("%p: %p,%p,%p,%p \n", i,testMat[i][0], testMat[i][1], testMat[i][2], testMat[i][3]);
	}*/

	mesh->SetActive();
	glDrawElements(GL_TRIANGLES, mesh->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}