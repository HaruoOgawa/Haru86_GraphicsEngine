#include "RectTransformComponent.h"
#include "./GameObject.h"
#include "./GameRenderer.h"
#include "./TransformComponent.h"
#include <iostream>
#include <string>


RectTransformComponent::RectTransformComponent(GameObject* o, float wRate, float hRate)
	:Component(o, static_cast<std::string>(typeid(RectTransformComponent).name()).substr(6))
{
	printf("superClassName: %s \n", superClassName.c_str());
	
	glm::vec2 size = static_cast<glm::vec2>(GameRenderer::GetInstance()->GetScreenSize());
	//rate -1.0 ~ 1.0
 	glm::vec2 pos = glm::vec2((size.x * 0.5) * wRate, (size.y * 0.5) * hRate);
	rectPosition = pos;

	printf("size: %f , %f \n", size.x, size.y);
	printf("rectPosition: %f , %f \n", rectPosition.x, rectPosition.y);
	
	pos = pos / (size * 0.5f);
	printf("normalize pos: %f , %f \n", pos.x, pos.y);
	owner->transform->position = glm::vec3(pos.x,pos.y, owner->transform->position.z);
}

RectTransformComponent::~RectTransformComponent() {

}

void RectTransformComponent::ProcessInput(const Uint8* state)const {

}