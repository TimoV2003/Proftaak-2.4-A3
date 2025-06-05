#include "PlayerComponent.h"
#include "I_InputStrategy.h"
#include <GLFW/glfw3.h>
#include <iostream>
extern GLFWwindow* window;

void PlayerComponent::update(float deltaTime) {
	if (auto p = getParent()) {
		p->position.x = inputstrategy->handlestrategy(p->position.x);

		std::cout << "Player position: " << p->position.x << std::endl;
	}
}