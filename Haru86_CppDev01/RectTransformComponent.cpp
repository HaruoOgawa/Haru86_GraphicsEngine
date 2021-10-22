#include "RectTransformComponent.h"
#include "./GameObject.h"
#include "./GameRenderer.h"
#include "./TransformComponent.h"

RectTransformComponent::RectTransformComponent(GameObject* o, float wRate, float hRate)
	:Component(o)
{
	glm::vec2 size = static_cast<glm::vec2>(GameRenderer::GetInstance()->GetScreenSize());
 	glm::vec2 pos = glm::vec2((size.x * 0.5) * wRate, (size.y * 0.5) * hRate);
	rectPosition = pos;

	printf("size: %f , %f \n", size.x, size.y);
	printf("rectPosition: %f , %f \n", rectPosition.x, rectPosition.y);
	/*owner->transform->position = */
	glm::vec4 trsPos=
		//glm::inverse(owner->transform->GetMMatrix())*
		//glm::inverse(owner->transform->GetVMatrix())*
		glm::inverse(owner->transform->vMatrix)*
		glm::vec4(0.0,0.0,0.0f,1.0f);
	printf("trsPos : %f , %f ,%f , %f \n", trsPos.x, trsPos.y, trsPos.z, trsPos.w);
	//pos / (size * 0.5f)
	owner->transform->position = glm::vec3(pos, 0.0f);
}

RectTransformComponent::~RectTransformComponent() {

}

void RectTransformComponent::ProcessInput(const Uint8* state)const {

}