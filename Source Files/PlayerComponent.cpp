#include "PlayerComponent.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "colour_detection.h"
#include <mutex>
#include <algorithm>

extern GLFWwindow* window;

void PlayerComponent::update(float deltaTime) {
	if (auto p = getParent()) {
		p->position.x = inputstrategy->handlestrategy(p->position.x, deltaTime);

	}
}