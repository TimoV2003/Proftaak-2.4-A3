#pragma once
#include "GameComponent.h"

class WalkAnimationComponent : public GameComponent {
private:
	float baseScale, scaleFactor, cyclePeriod, animationSpeedMult;
public:
	WalkAnimationComponent(float baseScale = 1.0f, float scaleFactor = 0.03f, float cyclePeriod = 2.0f, float animationSpeedMult = 3.0f) :
		baseScale(baseScale), scaleFactor(scaleFactor), cyclePeriod(cyclePeriod), animationSpeedMult(animationSpeedMult) {};
	~WalkAnimationComponent() = default;

	virtual void update(const float& deltaTime) override;
};