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
		return currentLocation -= speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		return currentLocation += speed;
	}
	else {
		return currentLocation;
	}
}