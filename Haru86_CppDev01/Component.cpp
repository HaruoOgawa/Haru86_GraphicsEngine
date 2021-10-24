#include "Component.h"
#include "./Game.h"

Component::Component(Object* o, std::string name)
	: owner(o),game(Game::GetInstance()), superClassName(name)
{

}

Component::~Component() {

}

void Component::Update() {

}

