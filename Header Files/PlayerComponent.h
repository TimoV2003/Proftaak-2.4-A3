#pragma once

#include "I_InputStrategy.h"
#include "GameComponent.h"
#include "GameObject.h"

class PlayerComponent : public GameComponent
{
	std::shared_ptr<IInputStrategy> inputstrategy;
public:
	PlayerComponent(std::shared_ptr<IInputStrategy> inputstrategy) :inputstrategy(inputstrategy) {};
	~PlayerComponent() = default;
	virtual void update(float deltaTime) override;

};
