#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "GameComponent.h"
#include "DrawComponent.h"
#include <string>


using tigl::Vertex;

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
		void GameObject::addComponent(std::shared_ptr<GameComponent> component);
		void GameObject::removeComponent(const std::string& id);
		std::shared_ptr<GameComponent> getComponent();

		void update();
		void draw();
};

