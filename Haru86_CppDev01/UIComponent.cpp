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

	float fx = static_cast<float>(x) - static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().x) * 0.5f;
	float fy = static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().y) * 0.5f- static_cast<float>(y);
	
	

	SDL_Event event;
	
	while (SDL_PollEvent(&event)) // check to see if an event has happened
	{
		switch (event.type)
		{
		case SDL_QUIT:
			break;
		case SDL_MOUSEBUTTONDOWN: // if the event is mouse click
			printf("Click");
		}
	}

	if (CheckInnnerBox(fx,fy)) {
		float maxLeftPointX = static_cast<RectTransformComponent*>(owner->
			GetComponent(static_cast<std::string>(typeid(RectTransformComponent).name())))->maxLeftPointX;
		float maxRightPointX = static_cast<RectTransformComponent*>(owner->
			GetComponent(static_cast<std::string>(typeid(RectTransformComponent).name())))->maxRightPointX;

		if (fx < maxLeftPointX) {
			fx = maxLeftPointX;
		}
		else if (fx>maxRightPointX) {
			fx = maxRightPointX;
		}

		float t = (maxLeftPointX-fx) / (maxLeftPointX-maxRightPointX);
		t = (t < 0.0f) ? 0.0f : t;
		printf("t : %f \n", t);
		
		float xval = fx / (static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().x) * 0.5f);
		float yval = fy / (static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().y) * 0.5f);
		
		glm::vec2 pos = glm::vec2(xval, yval);
		glm::vec4 modelPos =
			glm::inverse(owner->transform->GetPMatrix() * owner->transform->GetVMatrix())
			* glm::vec4(pos.x, pos.y, 0.0f, 1.0f);
		pos = glm::vec2(modelPos.x / modelPos.w, modelPos.y / modelPos.w);

		owner->SetPosition(glm::vec3(pos.x, owner->transform->position.y, owner->transform->position.z));
		static_cast<RectTransformComponent*>(owner->
			GetComponent(static_cast<std::string>(typeid(RectTransformComponent).name())))->rectPosition.x = fx;
	}
}

bool UIComponent::CheckInnnerBox( float x,  float y)const {
	glm::vec2 rectScale = static_cast<RectTransformComponent*>(owner->
		GetComponent(static_cast<std::string>(typeid(RectTransformComponent).name())))->rectScale;
	
	glm::vec2 rectPosition = static_cast<RectTransformComponent*>(owner->
		GetComponent(static_cast<std::string>(typeid(RectTransformComponent).name())))->rectPosition;

	glm::vec2 minPos = rectPosition - rectScale;
	glm::vec2 maxPos = rectPosition + rectScale;

	bool isInner = x< minPos.x ||
		y< minPos.y ||
		x>maxPos.x ||
		y>maxPos.y;

	return !isInner;
}