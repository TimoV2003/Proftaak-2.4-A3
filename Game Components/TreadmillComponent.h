#pragma once
#include "GameComponent.h"
#include "GameObject.h"

// this include section is needed for the treadmill strategy
#include "../patterns/strategy/interfaces/IEndOfMillBehavior.h"

class TreadmillComponent : public GameComponent {
	std::shared_ptr<IEndOfMillBehavior> endOfMillBehavior;
	const float maxEndCheckPausedTime;
	const int speed;
	const int deletionDistance;
public:
	TreadmillComponent(std::shared_ptr<IEndOfMillBehavior> endOfMillBehavior
		, float maxEndCheckPausedTime = 0.5f
		, int speed = 20
		, int deletionDistance = 40)
		: endOfMillBehavior(endOfMillBehavior) 
		, maxEndCheckPausedTime(maxEndCheckPausedTime)
		, speed(speed)
		, deletionDistance(deletionDistance)
	{};
	~TreadmillComponent() = default;

	virtual void update(const float& deltaTime) override;
};

