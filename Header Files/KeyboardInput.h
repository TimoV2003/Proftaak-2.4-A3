#pragma once
#include "I_InputStrategy.h"
#include <GLFW/glfw3.h>

class KeyboardInput : public IInputStrategy
{
	float speed = 0.1f;
public:
	KeyboardInput();
	~KeyboardInput();

	float handlestrategy(float currentLocation, float deltaTime) override;
};