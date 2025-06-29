#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <memory>
#include "GameComponent.h"
#include "DrawComponent.h"

class GameComponent;
class DrawComponent;
class GameService;

class GameObject : public std::enable_shared_from_this<GameObject>
{
private:
	std::vector<std::shared_ptr<GameComponent>> gameComponents;
	std::vector<std::shared_ptr<DrawComponent>> drawComponents;
	float collisionSize;
	std::string tag;
public:
	/// <summary>
	/// game service pointer, used to access the game service class for game logic.
	/// </summary>
	GameService* game;

	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);

	/// <param name="tag">Used to identify groups or individual gameobjects</param>
	/// <param name="collisionSize">Used during collision</param>
	GameObject(const std::string tag, float collisionSize = 1.0f);
	~GameObject();

	void addComponent(std::shared_ptr<GameComponent> component);
	void setGameService(GameService* gameService) { game = gameService; }

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
	std::shared_ptr<T2> getComponent() const;

	/// <summary>
	/// used primarily for debugging purposes. only returns the names of all components.
	/// </summary>
	std::vector<std::string> getAllComponentNames() const;

	void update(const float& deltaTime);
	void draw();

	float getCollisionSize() const { return collisionSize; }
	std::string getTag() const { return tag; }
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
std::shared_ptr<T2> GameObject::getComponent() const
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