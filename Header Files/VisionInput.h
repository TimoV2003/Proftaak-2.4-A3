#pragma once
#pragma once
#include "I_InputStrategy.h"
#include <GLFW/glfw3.h>

class VisionInput : public IInputStrategy
{
	float cameraWidth = 640.0f;
	float worldWidth = 20.0f;
	float worldOffset = 10.0f;
	bool cameraInversion = true;
public:
	VisionInput();
	~VisionInput();

	float handlestrategy(float currentLocation, float deltaTime) override;
};