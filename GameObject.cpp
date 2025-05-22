#include "GameObject.h"

GameObject::GameObject() {
	//TODO add logic: to be overwritten
}

GameObject::~GameObject() {
	//TODO add logic: to delete
}

void GameObject::addComponent(GameComponent gameComponent)
{
	//TODO add logic: add component
}

std::shared_ptr<GameComponent> GameObject::getComponent()
{
	//TODO add logic: get component of same type
	return std::shared_ptr<GameComponent>();
}

void GameObject::removeComponent(std::string id)
{
	//TODO add logic: remove component with ID
}

void GameObject::update()
{
	for (auto& component : gameComponents)
	{
		component.update();
	}
}

void GameObject::draw()
{
	for (auto& component : drawComponents)
	{
		component.draw();
	}
}

