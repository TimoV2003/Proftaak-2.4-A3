#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "ColourDetection.h"
#include <mutex>
#include <algorithm>

// this include section is needed for the input strategy
#include "../patterns/strategy/input_strategies/Headers/VisionInput.h"


extern GLFWwindow* window;

float VisionInput::handlestrategy(float currentLocation, float deltaTime) {
		float visionNormalisedPosition;
		{
			std::lock_guard<std::mutex> lock(vision::visionPositionMutex);
			visionNormalisedPosition = vision::visionNormalisedPosition;
		}


		float targetX = (visionNormalisedPosition * worldWidth) - worldOffset;

		if (cameraInversion) {
			targetX = targetX * -1;
		}

		float speed = 10.0f;
		
		return glm::mix(currentLocation, targetX, glm::clamp(speed * deltaTime, 0.0f, 1.0f));
}