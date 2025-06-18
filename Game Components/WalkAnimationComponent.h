#pragma once
#include "GameComponent.h"

class WalkAnimationComponent : public GameComponent {
public:
	WalkAnimationComponent() = default;
	~WalkAnimationComponent() = default;

	virtual void update(float deltaTime) override;
};