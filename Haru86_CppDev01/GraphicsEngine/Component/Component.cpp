#include "Component.h"
#include "../Game/Game.h"

Component::Component(std::shared_ptr<class Object> o, std::string name)
	: owner(o),game(Game::GetInstance()), superClassName(name)
{
	Start();
}

Component::~Component() {

}

void Component::Start() {
}

void Component::Update() {

}

