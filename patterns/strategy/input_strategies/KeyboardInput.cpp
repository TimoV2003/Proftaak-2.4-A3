// this include section is needed for the input strategy
#include "../patterns/strategy/input_strategies/Headers/KeyboardInput.h" 

extern GLFWwindow* window;

float KeyboardInput::handlestrategy(float currentLocation, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		
		currentLocation -= (this->speed * deltaTime);
		if (currentLocation < -worldWidth / 2) {
			currentLocation = -worldWidth / 2;
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		currentLocation += (this->speed * deltaTime);
		if (currentLocation > worldWidth / 2) {
			currentLocation = worldWidth / 2;
		}
	}

	return currentLocation;
}