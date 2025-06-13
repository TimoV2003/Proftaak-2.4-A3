#pragma once
#include "GameComponent.h"
#include "GameObject.h"

// this include section is needed for the treadmill strategy
#include "../patterns/strategy/interfaces/IEndOfMillBehavior.h"

class TreadmillComponent : public GameComponent
{
	std::shared_ptr<IEndOfMillBehavior> endOfMillBehavior;
	const float maxEndCheckPausedTime = 1.0f;
	int speed = 20;
	int deletionDistance = 10;
	bool EndCheckPaused = false;
public:
	TreadmillComponent(std::shared_ptr<IEndOfMillBehavior> endOfMillBehavior) : endOfMillBehavior(endOfMillBehavior) {};
	~TreadmillComponent() = default;

	virtual void update(float deltaTime) override;
};

