#include "Component.h"
#include "../Game/Game.h"

Component::Component(Object* o)
	: owner(o),game(Game::GetInstance())
{
	Start();
}

Component::~Component() {
}

void Component::Start() {
}

void Component::Update() {

}

void Component::Dtaw() {
}

