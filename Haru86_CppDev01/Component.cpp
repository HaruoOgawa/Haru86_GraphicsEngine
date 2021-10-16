#include "Component.h"
#include "./Game.h"

Component::Component(Object* o)
	: owner(o),game(Game::GetInstance())
{

}

Component::~Component() {

}

void Component::Update() {

}