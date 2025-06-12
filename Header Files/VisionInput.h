#pragma once
#pragma once
#include "I_InputStrategy.h"
#include <GLFW/glfw3.h>

class VisionInput : public IInputStrategy
{
	float worldWidth;
	float worldOffset;
	bool cameraInversion = true;
public:
	
	/// <param name="worldWidth">bounds player movement to the width of the world</param>
	VisionInput(float worldWidth = 20.0f) : worldWidth(worldWidth) { worldOffset = worldWidth / 2.0f; };
	~VisionInput() = default;

	float handlestrategy(float currentLocation, float deltaTime) override;
};