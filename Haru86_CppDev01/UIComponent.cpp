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
	const float fy = static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().y) * 0.5f- static_cast<float>(y);
	
	//float xval = fx / (static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().x) * 0.5f);
	//printf("xval: %f \n", xval);

	if (CheckInnnerBox(fx,fy)) {
		printf("Mouse enter ui box \n");
		float xval = fx / (static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().x) * 0.5f);
		float yval = fy / (static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().y) * 0.5f);
		printf("xval: %f \n", xval);
		glm::vec2 pos = glm::vec2(xval, yval);
		glm::vec4 modelPos =
			glm::inverse(owner->transform->GetPMatrix() * owner->transform->GetVMatrix())
			* glm::vec4(pos.x, pos.y, 0.0f, 1.0f);
		pos = glm::vec2(modelPos.x / modelPos.w, modelPos.y / modelPos.w);

		//owner->transform->position = glm::vec3(pos.x, owner->transform->position.y,owner->transform->position.z);
		owner->SetPosition(glm::vec3(pos.x, owner->transform->position.y, owner->transform->position.z));
		static_cast<RectTransformComponent*>(owner->
			GetComponent(static_cast<std::string>(typeid(RectTransformComponent).name())))->rectPosition.x = fx;
	}


	//printf("x: %d ,y: %d \n",x,y);
	//printf("fx : %f , fy : %f \n",fx,fy);

	/*glm::vec2 rectPosition =static_cast<RectTransformComponent*>(owner->
		GetComponent(static_cast<std::string>(typeid(RectTransformComponent).name())))->rectPosition;
	printf("rectPosition: %f , %f \n", rectPosition.x, rectPosition.y);

	glm::vec2 rectScale = static_cast<RectTransformComponent*>(owner->
		GetComponent(static_cast<std::string>(typeid(RectTransformComponent).name())))->rectScale;
	printf("rectScale: %f , %f \n", rectScale.x, rectScale.y);*/
}

bool UIComponent::CheckInnnerBox( float x,  float y)const {
	glm::vec2 rectScale = static_cast<RectTransformComponent*>(owner->
		GetComponent(static_cast<std::string>(typeid(RectTransformComponent).name())))->rectScale;
	//rectScale = glm::vec2(10.0f, 10.0f);

	glm::vec2 rectPosition = static_cast<RectTransformComponent*>(owner->
		GetComponent(static_cast<std::string>(typeid(RectTransformComponent).name())))->rectPosition;

	glm::vec2 minPos = rectPosition - rectScale;
	glm::vec2 maxPos = rectPosition + rectScale;

	/*printf("rectPosition: %f , %f \n", rectPosition.x, rectPosition.y);
	printf("rectScale: %f , %f \n", rectScale.x, rectScale.y);
	printf("fx fy: %f , %f \n", x,y);*/


	bool isInner = x< minPos.x ||
		y< minPos.y ||
		x>maxPos.x ||
		y>maxPos.y;

	//printf("minPos: %f,%f \n", minPos.x, minPos.y);
	//printf("maxPos: %f,%f \n", maxPos.x, maxPos.y);

	return !isInner;
}