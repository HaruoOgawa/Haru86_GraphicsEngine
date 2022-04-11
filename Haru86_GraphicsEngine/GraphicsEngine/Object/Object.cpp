#include "Object.h"

#include "../Component/TransformComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../GraphicsMain/GraphicsMain.h"

Object::Object()
	: game(GraphicsMain::GetInstance())
{
	transform = std::make_shared<TransformComponent>(this, glm::vec3(0,0,0),  glm::quat(glm::vec3(0,0,0)),  glm::vec3(1.0f,1.0f,1.0f));
	Object::AddComponent<TransformComponent>(transform);
}

Object::~Object() {
	myComponent.clear();
}

void Object::RemoveComponent(std::shared_ptr<class Component> component) {
	
}

void Object::Update() {
	for (auto comp : myComponent) {
		comp.second->Update();
	}
}

void Object::ProcessInput(const SDL_Event& e) {
	for (auto comp : myComponent) {
		comp.second->ProcessInput(e);
	}
}

void Object::SetTransform(glm::vec3 pos, glm::quat rot, glm::vec3 s)
{ 
	transform->SetPosition(pos);
	transform->SetRotation(rot); 
	transform->SetScale(s); 

	transform->CalMatrix();
}

void Object::SetPosition(glm::vec3 pos) {
	transform->SetPosition(pos);

	transform->CalMatrix();
}

void Object::SetRotation(glm::quat rot) {
	transform->SetRotation(rot);

	transform->CalMatrix();
}
void Object::SetScale(glm::vec3 s) {
	transform->SetScale(s);

	transform->CalMatrix();
}

glm::vec3 Object::GetPosition() {
	return transform->GetPosition();
}

glm::quat Object::GetRotation() {
	return transform->GetRotation();
}

glm::vec3 Object::GetScale() {
	return transform->GetScale();
}