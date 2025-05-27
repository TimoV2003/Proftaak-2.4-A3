#include "PlayerComponent.h"
#include "I_InputStrategy.h"
#include <GLFW/glfw3.h>
#include <iostream>
extern GLFWwindow* window;

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::update() {
	parent->position.x = inputstrategy->handlestrategy(parent->position.x);

	std::cout << "Player position: " << parent->position.x << std::endl;
}