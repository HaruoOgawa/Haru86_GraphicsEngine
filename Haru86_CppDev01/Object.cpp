#include "Object.h"

#include "./TransformComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "./Game.h"

Object::Object()
	: game(Game::GetInstance())
{
	transform = new TransformComponent(this, glm::vec3(0,0,0),  glm::quat(glm::vec3(0,0,0)),  glm::vec3(1.0f,1.0f,1.0f));
	Object::AddComponent(transform);
}

Object::~Object() {
	for (auto comp : myComponent) {
		RemoveComponent(comp.second);
	}
	myComponent.clear();
}

void Object::AddComponent(Component* component) {
	myComponent.insert({ component->superClassName,component });
}


void Object::RemoveComponent(Component* component) {
	delete  component;
}


Component* Object::GetComponent(std::string componentName) {
	auto item = myComponent.find(componentName.substr(6));
	return item->second;
}

void Object::Update() {
	for (auto comp : myComponent) {
		comp.second->Update();
	}
}

void Object::SetTransform(glm::vec3 pos, glm::quat rot, glm::vec3 s)
{ 
	transform->position = pos;
	transform->rotation = rot; 
	transform->scale = s; 

	transform->CalMatrix();
}

void Object::SetPosition(glm::vec3 pos) {
	transform->position = pos;

	transform->CalMatrix();
}

void Object::SetRotation(glm::quat rot) {
	transform->rotation;

	transform->CalMatrix();
}
void Object::SetScale(glm::vec3 s) {
	transform->scale = s;

	transform->CalMatrix();
}

glm::vec3 Object::GetPosition() {
	return transform->position;
}

glm::quat Object::GetRotation() {
	return transform->rotation;
}

glm::vec3 Object::GetScale() {
	return transform->scale;
}