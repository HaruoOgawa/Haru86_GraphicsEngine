#include "Object.h"

#include "../Component/TransformComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../Game/Game.h"

Object::Object()
	: game(Game::GetInstance())
{
	transform = std::make_shared<TransformComponent>(this, glm::vec3(0,0,0),  glm::quat(glm::vec3(0,0,0)),  glm::vec3(1.0f,1.0f,1.0f));
	Object::AddComponent<TransformComponent>(transform);
}

Object::~Object() {
	myComponent.clear();
}

/*
void Object::AddComponent(std::shared_ptr<class Component> component) {
	myComponent.insert({ component->superClassName,component});
}*/

void Object::RemoveComponent(std::shared_ptr<class Component> component) {
	
}

/*
Component* Object::GetComponent(std::string componentName) {
	auto item = myComponent.find(componentName.substr(6));
	return item->second.get();
}*/

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
	transform->rotation=rot;

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