#include "Component.h"
#include "../Game/Game.h"

Component::Component(Object* o, std::string name)
	: owner(o),game(Game::GetInstance()), superClassName(name)
{
	Start();
}

Component::~Component() {
	printf("Component is Called\n");
}

void Component::Start() {
}

void Component::Update() {

}

