#include "PlayerComponent.h"
#include "I_InputStrategy.h"
#include <GLFW/glfw3.h>
#include <iostream>
extern GLFWwindow* window;

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::update() {
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		std::cout << "A" << std::endl;
		parent->position.x -= 20;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		std::cout << "D" << std::endl;
		parent->position.x += 20;
}