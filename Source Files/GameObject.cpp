#include "GameObject.h"
#include "tigl.h"
#include <iostream>
#if _DEBUG
#include "DebugReferenceCounter.h"
#endif

GameObject::GameObject(const std::string tag, float collisionSize) : tag(tag), game(nullptr), collisionSize(collisionSize) {
#if _DEBUG
	DebugReferenceCounter::IncrementObjectReferenceCounter();
#endif
}

GameObject::~GameObject() {
#if _DEBUG
	DebugReferenceCounter::DecrementObjectReferenceCounter();
#endif
}

void GameObject::addComponent(std::shared_ptr<GameComponent> component) {
	if (std::shared_ptr<DrawComponent> draw = std::dynamic_pointer_cast<DrawComponent>(component)) {
		drawComponents.push_back(draw);
		draw->setGameObject(shared_from_this());
		return;
	}
	gameComponents.push_back(component);
	component->setGameObject(shared_from_this());
}

std::vector<std::string> GameObject::getAllComponentNames() {
	std::vector<std::string> names = {};
	for (const auto& gameComponent : gameComponents) {
		if (gameComponent) {
			names.push_back(typeid(*gameComponent).name());
		}
	}
	for (const auto& drawComponent : drawComponents) {
		if (drawComponent) {
			names.push_back(typeid(*drawComponent).name());
		}
	}
	return names;
}

void GameObject::update(float deltaTime) {
	for (auto& component : gameComponents) 
	{
		component->update(deltaTime);
	}
	for (auto& component : drawComponents)
	{
		component->update(deltaTime);
	}
}

void GameObject::draw() {
	for (auto& component : drawComponents)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), scale) 
			* glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1,0,0))
			* glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0, 1,0))
			* glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0, 0,1));

//		tigl::shader->enableColor(true);
		tigl::shader->setModelMatrix(model);

		component->draw();
	}
}

std::string GameObject::getTag()
{
	return tag;
}

