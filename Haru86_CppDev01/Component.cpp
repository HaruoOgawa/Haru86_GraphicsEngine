#include "Component.h"

Component::Component(Game* g,Object* o)
	: owner(o),game(g)
{

}

Component::~Component() {

}

void Component::Update() {

}