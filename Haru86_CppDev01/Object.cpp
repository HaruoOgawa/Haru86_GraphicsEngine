#include "Object.h"

#include "./TransformComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

Object::Object(Game* g)
	: game(g)
{
	TransformComponent* transform = new TransformComponent(this, glm::vec3(0,0,0),glm::quat(glm::vec3(0,0,0)),glm::vec3(1,1,1));
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