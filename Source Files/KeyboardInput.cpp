#include "KeyboardInput.h"

extern GLFWwindow* window;

KeyboardInput::KeyboardInput()
{
}

KeyboardInput::~KeyboardInput()
{
}

float KeyboardInput::handlestrategy(float currentLocation)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		currentLocation -= speed;
		if (currentLocation < -11.0f) {
			currentLocation = -11.0f;
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		currentLocation += speed;
		if (currentLocation > 11.0f) {
			currentLocation = 11.0f;
		}
	}

	return currentLocation;
}