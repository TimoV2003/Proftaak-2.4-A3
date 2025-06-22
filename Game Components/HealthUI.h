#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GameComponent.h"

class HealthComponent;

class HealthUI : public GameComponent
{
private:
	std::shared_ptr<HealthComponent> healthComponent;
	GLFWwindow* window;
public:
	HealthUI(std::shared_ptr<HealthComponent> healthComponent, GLFWwindow* window);
	~HealthUI() = default;
	void drawLate();
	
};

