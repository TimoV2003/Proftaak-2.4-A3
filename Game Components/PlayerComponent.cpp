#include "PlayerComponent.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "ColourDetection.h"
#include <mutex>
#include <algorithm>

extern GLFWwindow* window;

void PlayerComponent::update(const float& deltaTime) {
	if (auto p = getParent()) {
		p->position.x = inputstrategy->handlestrategy(p->position.x, deltaTime);

	}
}