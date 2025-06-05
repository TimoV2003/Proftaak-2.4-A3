#include "VisionInput.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "colour_detection.h"
#include <mutex>
#include <algorithm>


extern GLFWwindow* window;

VisionInput::VisionInput()
{
}

VisionInput::~VisionInput()
{
}

float VisionInput::handlestrategy(float currentLocation, float deltaTime)
{
		cv::Point visionPosition;
		{
			std::lock_guard<std::mutex> lock(vision::visionPositionMutex);
			visionPosition = vision::visionPosition;
		}

		float cameraWidth = 640.0f;
		float worldMinX = -10.0f, worldMaxxX = 10.0f;
		float normX = visionPosition.x / cameraWidth;
		normX = glm::clamp(normX, 0.0f, 1.0f);
		float targetX = worldMinX + normX * (worldMaxxX - worldMinX);

		float speed = 10.0f;
		
		return glm::mix(currentLocation, targetX, glm::clamp(speed * deltaTime, 0.0f, 1.0f));
}