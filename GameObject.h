#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "GameComponent.h"
#include <string>
using tigl::Vertex;

class GameObject
{
	private:
		std::vector<GameComponent> gameComponents = {};
		//std::vector<DrawComponent> gameComponents = {};
		glm::vec3 position = glm::vec3(0, 0, 0);
		glm::vec3 rotation = glm::vec3(0, 0, 0);
		glm::vec3 scale = glm::vec3(0, 0, 0);

	public: 
		GameObject();
		~GameObject();
		void addComponent(GameComponent gameComponent);
		std::shared_ptr<GameComponent> getComponent();
		void removeComponent(std::string id);

		void update();
		void draw();
};

