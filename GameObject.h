#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <memory>
#include "GameComponent.h"
#include "DrawComponent.h"

class GameObject
{
	private:
		std::vector<std::shared_ptr<GameComponent>> gameComponents;
		std::vector<std::shared_ptr<DrawComponent>> drawComponents;
		glm::vec3 position = glm::vec3(0, 0, 0);
		glm::vec3 rotation = glm::vec3(0, 0, 0);
		glm::vec3 scale = glm::vec3(0, 0, 0);

	public: 
		GameObject();
		~GameObject();
		void addComponent(std::shared_ptr<GameComponent> component);
		void removeComponent(const std::string& id);
		std::shared_ptr<GameComponent> getComponent();

		void update();
		void draw();
};

