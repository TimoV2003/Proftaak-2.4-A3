#pragma once
#include <GLFW/glfw3.h>

// this include section is needed for the input strategy
#include "../patterns/strategy/interfaces/I_InputStrategy.h"

class KeyboardInput : public IInputStrategy
{
	float speed = 4.0f;
public:
	KeyboardInput() = default;
	~KeyboardInput() = default;

	float handlestrategy(float currentLocation, float deltaTime) override;
};