// this include section is needed for the input strategy
#include "../patterns/strategy/input_strategies/Headers/KeyboardInput.h" 

extern GLFWwindow* window;

float KeyboardInput::handlestrategy(float currentLocation, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		
		currentLocation -= (this->speed * deltaTime);
		if (currentLocation < -11.0f) {
			currentLocation = -11.0f;
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		currentLocation += (this->speed * deltaTime);
		if (currentLocation > 11.0f) {
			currentLocation = 11.0f;
		}
	}

	return currentLocation;
}