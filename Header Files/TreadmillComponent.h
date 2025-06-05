#pragma once
#include "GameComponent.h"
#include "GameObject.h"
#include "IEndOfMillBehavior.h"
class TreadmillComponent : public GameComponent
{
	std::shared_ptr<IEndOfMillBehavior> endOfMillBehavior;
	int speed = 2;
	int deletionDistance = 10;
public:
	TreadmillComponent(std::shared_ptr<IEndOfMillBehavior> endOfMillBehavior) : endOfMillBehavior(endOfMillBehavior) {};
	~TreadmillComponent() = default;

	virtual void update(float deltaTime) override;
};

