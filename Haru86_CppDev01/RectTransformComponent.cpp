#include "RectTransformComponent.h"
#include "./GameObject.h"
#include "./GameRenderer.h"
#include "./TransformComponent.h"
#include <iostream>
#include <string>
#include <glm/glm.hpp>

RectTransformComponent::RectTransformComponent(GameObject* o, float wRate, float hRate)
	:Component(o, static_cast<std::string>(typeid(RectTransformComponent).name()).substr(6))
{
	printf("superClassName: %s \n", superClassName.c_str());
	
	glm::vec2 size = static_cast<glm::vec2>(GameRenderer::GetInstance()->GetScreenSize());
	//rate 0.0 ~ 1.0
 	glm::vec2 pos = glm::vec2(size.x * wRate -size.x * 0.5, size.y * hRate - size.y * 0.5);
	//pos.y = -pos.y;
	rectPosition = pos;

	printf("size: %f , %f \n", size.x, size.y);
	printf("rectPosition: %f , %f \n", rectPosition.x, rectPosition.y);
	
	pos = pos / (size * 0.5f);
	//printf("size * 0.5f : %f , %f \n", size.x * 0.5f, size.y * 0.5f);
	//printf("normalize rectPosition: %f , %f \n", pos.x, pos.y);
	glm::vec4 modelPos = 
		glm::inverse(owner->transform->GetPMatrix() *owner->transform->GetVMatrix())
		* glm::vec4(pos.x, pos.y, 0.0f, 1.0f);
	pos = glm::vec2(modelPos.x/ modelPos.w, modelPos.y/ modelPos.w);
	//printf("normalize pos: %f , %f \n", pos.x, pos.y);
	owner->SetPosition(glm::vec3(pos.x, pos.y, modelPos.z / modelPos.w));

	glm::vec4 uiScreenScale =  owner->transform->GetVMatrix() * glm::vec4(owner->transform->scale, 1.0f);
	rectScale = glm::vec2(glm::abs(uiScreenScale.x)*size.x*0.5, glm::abs(uiScreenScale.y) * size.y*0.5);
	//printf("rectScale: %f , %f \n", rectScale.x, rectScale.y);
	
	//uiScreenScale = glm::inverse( owner->transform->GetVMatrix()) * glm::vec4(-0.100000, 0.050000, -4.000000, 1.0f);
	//printf("uiScreenScale Inverse: %f , %f , %f \n", uiScreenScale.x/ uiScreenScale.w, uiScreenScale.y/ uiScreenScale.w, uiScreenScale.z/ uiScreenScale.w);
}

RectTransformComponent::~RectTransformComponent() {

}

void RectTransformComponent::ProcessInput(const Uint8* state)const {

}