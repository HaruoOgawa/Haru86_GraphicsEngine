#include "UIComponent.h"
#include "./GameObject.h"
#include "./Game.h"
#include <SDL.h>

UIComponent::UIComponent(GameObject* o)
	: Component(o)
{
	o->UseZTest(false);
	o->SetRenderOlder(RenderQueue::UI);
}

UIComponent::~UIComponent() {

}

void UIComponent::ProcessInput(const Uint8* state) const {
	printf("Hello ProcessInput of UIComp \n");
	int x, y;
	SDL_GetMouseState(&x, &y);
	printf("Mouse Pos : x=%d , y=%d \n",static_cast<int>(x),static_cast<int>(y));
}
