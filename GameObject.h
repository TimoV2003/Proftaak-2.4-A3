#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <memory>
#include "GameComponent.h"
#include "DrawComponent.h"

class GameComponent;
class DrawComponent;

class GameObject
{
private:
	std::vector<std::shared_ptr<GameComponent>> gameComponents;
	std::vector<std::shared_ptr<DrawComponent>> drawComponents;
	std::string id;
public:
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(0, 0, 0);

	GameObject(const std::string id) : id(id) {};
	~GameObject() = default;

	void addComponent(std::shared_ptr<GameComponent> component);

	template<typename T1> 
	void removeComponent();

	template<typename T2> 
	std::shared_ptr<T2> getComponent();

	void update();
	void draw();
};
