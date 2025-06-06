#pragma once
#pragma once
#include "I_InputStrategy.h"
#include <GLFW/glfw3.h>

class VisionInput : public IInputStrategy
{
public:
	VisionInput();
	~VisionInput();

	float handlestrategy(float currentLocation, float deltaTime) override;
};