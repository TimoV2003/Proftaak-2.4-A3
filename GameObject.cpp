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
	gameComponents.erase(
		std::remove_if(gameComponents.begin(), gameComponents.end(),
			[](const std::shared_ptr<GameComponent>& component) {
				return std::dynamic_pointer_cast<T1>(component) != nullptr;
			})
		, gameComponents.end()
	);

	drawComponents.erase(
		std::remove_if(drawComponents.begin(), drawComponents.end(),
			[](const std::shared_ptr<GameComponent>& component) {
				return std::dynamic_pointer_cast<T1>(component) != nullptr;
			})
		, drawComponents.end()
	);
}

template<typename T2>
std::shared_ptr<T2> GameObject::getComponent()
{
	for (const std::shared_ptr<GameComponent>& gameComponent : gameComponents) {
		std::shared_ptr<T2> casted = std::dynamic_pointer_cast<T2>(gameComponent);
		if (casted) {
			return casted;
		}
	}
	for (const std::shared_ptr<DrawComponent>& drawComponent : drawComponents) {
		std::shared_ptr<T2> casted = std::dynamic_pointer_cast<T2>(drawComponent);
		if (casted) {
			return casted;
		}
	}
	return nullptr;
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

