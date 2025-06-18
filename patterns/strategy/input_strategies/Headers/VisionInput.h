#pragma once
#include <GLFW/glfw3.h>

// this include section is needed for the input strategy
#include "../patterns/strategy/interfaces/I_InputStrategy.h"

class VisionInput : public IInputStrategy
{
	float worldWidth;
	float worldOffset;
	bool cameraInversion = true;
public:
	
	/// <param name="worldWidth">bounds player movement to the width of the world</param>
	VisionInput(float worldWidth = 10.0f) : worldWidth(worldWidth) { worldOffset = worldWidth / 2.0f; };
	~VisionInput() = default;

	float handlestrategy(float currentLocation, float deltaTime) override;
};