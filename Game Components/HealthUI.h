#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "DrawComponent.h"

class HealthComponent;

class HealthUI : public DrawComponent
{
private:
	std::shared_ptr<HealthComponent> healthComponent;
	GLFWwindow* window;
public:
	HealthUI(std::shared_ptr<HealthComponent> healthComponent, GLFWwindow* window);
	~HealthUI() = default;
	virtual void draw() override;
	
};

