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
	if (std::shared_ptr<DrawComponent> drawComponent = std::dynamic_pointer_cast<DrawComponent>(component)) {
		this->drawComponents.push_back(drawComponent);
		drawComponent->setGameObject(shared_from_this());
		return;
	}
	this->gameComponents.push_back(component);
	component->setGameObject(shared_from_this());
}

std::vector<std::string> GameObject::getAllComponentNames() const {
	std::vector<std::string> names = {};
	for (const auto& gameComponent : this->gameComponents) {
		if (gameComponent) {
			names.push_back(typeid(*gameComponent).name());
		}
	}
	for (const auto& drawComponent : this->drawComponents) {
		if (drawComponent) {
			names.push_back(typeid(*drawComponent).name());
		}
	}
	return names;
}

void GameObject::update(const float& deltaTime) {
	for (auto& component : this->gameComponents)
	{
		component->update(deltaTime);
	}
	for (auto& component : this->drawComponents)
	{
		component->update(deltaTime);
	}
}

void GameObject::draw() {
	for (auto& component : this->drawComponents)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), scale) 
			* glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1,0,0))
			* glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0, 1,0))
			* glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0, 0,1));

		tigl::shader->setModelMatrix(model);

		component->draw();
	}
}