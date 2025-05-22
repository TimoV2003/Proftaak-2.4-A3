#include "GameObject.h"

GameObject::GameObject() {
	//TODO add logic: to be overwritten
}

GameObject::~GameObject() {
	//TODO add logic: to delete
}

void GameObject::addComponent(std::shared_ptr<GameComponent> component) {
	gameComponents.push_back(component);
}

void GameObject::removeComponent(const std::string& id) {
	gameComponents.erase(
		std::remove_if(gameComponents.begin(), gameComponents.end(),
			[&](const std::shared_ptr<GameComponent>& component) {
				return component->getId() == id;
			}),
		gameComponents.end()
	);
}

std::shared_ptr<GameComponent> GameObject::getComponent() {
	//TODO add logic: get component of same type
	return std::shared_ptr<GameComponent>();
}

void GameObject::update() {
	for (auto& component : gameComponents) 
	{
		component->update();
	}
}

void GameObject::draw() {
	for (auto& component : drawComponents)
	{
		component.draw();
	}
}

