#pragma once

#include "GameComponent.h"
#include "GameObject.h"

// this include section is needed for the input strategy
#include "../patterns/strategy/interfaces/I_InputStrategy.h"

class PlayerComponent : public GameComponent {
	std::shared_ptr<IInputStrategy> inputstrategy;
public:
	PlayerComponent(std::shared_ptr<IInputStrategy> inputstrategy) :inputstrategy(inputstrategy) {};
	~PlayerComponent() = default;
	virtual void update(const float& deltaTime) override;
};
