#include "GameObject.h"

#include "./Transform.h"
#include "./Mesh.h"
#include "./Material.h"

GameObject::GameObject(Game* g)
	: game(g)
{
	Transform* defaultTRS = new Transform(this);
	Mesh* defaultMesh = new Mesh(this);
	Material* defaultMaterial = new Material(this);
}

GameObject::~GameObject() {
	for (auto comp : myComponent) {
		RemoveComponent(comp.second);
	}
}

void GameObject::AddComponent(Component* component) {
	myComponent.emplace(static_cast<std::string>(typeid(component).name()), component);
}
void GameObject::RemoveComponent(Component* component) {
	delete  component;
}

/*Component* GameObject::GetComponent() {

}*/