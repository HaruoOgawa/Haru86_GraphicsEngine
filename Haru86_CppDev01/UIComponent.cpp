#include "UIComponent.h"
#include "./GameObject.h"
#include "./Game.h"
#include <SDL.h>
#include "./GameRenderer.h"
#include <glm/glm.hpp>
#include "./TransformComponent.h"
#include "./RectTransformComponent.h"

UIComponent::UIComponent(GameObject* o)
	: Component(o, static_cast<std::string>(typeid(UIComponent).name()).substr(6))
{
	o->UseZTest(false);
	o->SetRenderOlder(RenderQueue::UI);
}

UIComponent::~UIComponent() {

}

void UIComponent::ProcessInput(const Uint8* state) const {
	int x, y;
	SDL_GetMouseState(&x, &y);

	/*const float fx = ((static_cast<float>(x) / static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().x))
		* 2.0f - 0.75f)
		*4.0f/3.0f;
	const float fy = ((static_cast<float>(y) / static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().y))
		* 2.0f - 0.75f)
		* 4.0f / 3.0f;*/
	
	//const float fx = (static_cast<float>(x) / static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().x)) * 2.0f - 1.0f;
	//const float fy = (static_cast<float>(y) / static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().y)) * 2.0f - 1.0f;
	
	const float fx = static_cast<float>(x) - static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().x) * 0.5f;
	const float fy = static_cast<float>(x) - static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().x) * 0.5f;


	/*if (CheckInnnerBox(fx,fy)) {
		printf("Mouse enter ui box \n");
		owner->transform->position = glm::vec3(-fx, owner->transform->position.y,owner->transform->position.z);
	}*/


	//printf("x: %d ,y: %d \n",x,y);
	//printf("fx : %f , fy : %f \n",fx,fy);

	glm::vec2 rectPosition =static_cast<RectTransformComponent*>(owner->
		GetComponent(static_cast<std::string>(typeid(RectTransformComponent).name())))->rectPosition;
	printf("rectPosition: %f , %f \n", rectPosition.x, rectPosition.y);

}

bool UIComponent::CheckInnnerBox( float x,  float y)const {
	glm::vec3 scale = owner->transform->scale;

	glm::vec3 pos = owner->transform->position-glm::vec3(scale.x*2.0f, scale.y * 2.0f,0.0f);
	glm::vec4 minPos = owner->transform->GetVMatrix() * owner->transform->GetMMatrix()
		* glm::vec4(pos.x, pos.y, pos.z, 1.0f);
	
	pos = owner->transform->position + glm::vec3(scale.x * 2.0f, scale.y * 2.0f, 0.0f);
	glm::vec4 maxPos = owner->transform->GetVMatrix() * owner->transform->GetMMatrix()
		* glm::vec4(pos.x, pos.y, pos.z, 1.0f);

	bool isInner = x> minPos.x ||
		y< minPos.y ||
		x<maxPos.x ||
		y>maxPos.y;

	printf("minPos: %f,%f,%f \n", minPos.x, minPos.y, minPos.z);
	printf("maxPos: %f,%f,%f \n", maxPos.x, maxPos.y, maxPos.z);

	return !isInner;
}