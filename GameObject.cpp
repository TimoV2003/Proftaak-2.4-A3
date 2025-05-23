#include "GameObject.h"

void GameObject::addComponent(std::shared_ptr<GameComponent> component) {
	if (std::shared_ptr<DrawComponent> draw = std::dynamic_pointer_cast<DrawComponent>(component)) {
		drawComponents.push_back(draw);
		return;
	}
	gameComponents.push_back(component);
}

template<typename T1>
inline void GameObject::removeComponent()
{

}

template<typename T2>
std::shared_ptr<GameComponent> GameObject::getComponent()
{
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
		component->draw();
	}
}

