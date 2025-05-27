#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <memory>
#include "GameComponent.h"
#include "DrawComponent.h"

class GameComponent;
class DrawComponent;

class GameObject : public std::enable_shared_from_this<GameObject>
{
private:
	std::vector<std::shared_ptr<GameComponent>> gameComponents;
	std::vector<std::shared_ptr<DrawComponent>> drawComponents;
	std::string id;
public:
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);

	GameObject(const std::string id) : id(id) {}
	~GameObject() = default;

	void addComponent(std::shared_ptr<GameComponent> component);
	void setGameService();

	/// <summary>
	/// removes a component based on type, removes all components of said type
	/// </summary>
	/// <typeparam name="T1">the component type to be removed</typeparam>
	template<typename T1> 
	void removeComponent();

	/// <summary>
	/// gets the first component it can find of the given type, if not found returns nullptr
	/// </summary>
	/// <typeparam name="T2">component type</typeparam>
	/// <returns>component object or nullptr</returns>
	template<typename T2> 
	std::shared_ptr<T2> getComponent();

	
	void update(float deltaTime);
	void draw();
};

// to prevent the use of a TPP file we have put the template functions here.

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