#include "Object.h"

#include "./TransformComponent.h"

Object::Object(Game* g)
	: game(g)
{
	TransformComponent* transform = new TransformComponent(this);
	Object::AddComponent(transform);
}

Object::~Object() {
	for (auto comp : myComponent) {
		RemoveComponent(comp.second);
	}
}

void Object::AddComponent(Component* component) {
	myComponent.emplace(static_cast<std::string>(typeid(component).name()), component);
}
void Object::RemoveComponent(Component* component) {
	delete  component;
}

/*Component* GameObject::GetComponent() {

}*/