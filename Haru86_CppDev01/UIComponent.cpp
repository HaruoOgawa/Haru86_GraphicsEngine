#include "UIComponent.h"
#include "./GameObject.h"
#include "./Game.h"
#include <SDL.h>
#include "./GameRenderer.h"
#include <glm/glm.hpp>
#include "./TransformComponent.h"

UIComponent::UIComponent(GameObject* o)
	: Component(o)
{
	o->UseZTest(false);
	o->SetRenderOlder(RenderQueue::UI);
}

UIComponent::~UIComponent() {

}

void UIComponent::ProcessInput(const Uint8* state) const {
	/*int x, y;
	SDL_GetMouseState(&x, &y);
	const float fx = (static_cast<float>(x) / static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().x))
		* 2.0f - 1.0f;
	const float fy = (static_cast<float>(y) / static_cast<float>(GameRenderer::GetInstance()->GetScreenSize().y))
		* 2.0f - 1.0f;

	if (CheckInnnerBox(fx,fy)) {
		printf("Mouse enter ui box ");
	}*/

}

bool UIComponent::CheckInnnerBox( float x,  float y)const {
	glm::vec3 pos = owner->transform->position-glm::vec3(0.5f,0.5f,0.0f);
	glm::vec4 minPos = owner->transform->GetVMatrix() * owner->transform->GetMMatrix()
		* glm::vec4(pos.x, pos.y, pos.z, 1.0f);
	
	pos = owner->transform->position + glm::vec3(0.5f, 0.5f, 0.0f);
	glm::vec4 maxPos = owner->transform->GetVMatrix() * owner->transform->GetMMatrix()
		* glm::vec4(pos.x, pos.y, pos.z, 1.0f);

	bool isInner = x< minPos.x ||
		y< minPos.y ||
		x>maxPos.x ||
		y>maxPos.y;

	return !isInner;
}