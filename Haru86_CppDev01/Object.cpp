#include "Object.h"

#include "./TransformComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

Object::Object(Game* g)
	: game(g)
{
	transform = new TransformComponent(g,this,new glm::vec3(0,0,0), new glm::quat(glm::vec3(0,0,0)), new glm::vec3(1.0f,1.0f,1.0f));
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

Component* Object::GetComponent(std::string componentName) {
	decltype(myComponent)::iterator item = myComponent.find(componentName);
	return item->second;
}