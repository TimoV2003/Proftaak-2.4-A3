#pragma once
// this include section is needed for the treadmill strategy
#include "../patterns/strategy/interfaces/IEndOfMillBehavior.h"

class EntityMillBehavior : public IEndOfMillBehavior
{
public:
	EntityMillBehavior() = default;
	~EntityMillBehavior() = default;

	void ReachedEndOfMill(std::shared_ptr<GameObject> parent) override;
};

