#pragma once
// this include section is needed for the treadmill strategy
#include "../patterns/strategy/interfaces/IEndOfMillBehavior.h"

class FloorMillBehavior : public IEndOfMillBehavior
{
public:
	FloorMillBehavior() = default;
	~FloorMillBehavior() = default;

	void ReachedEndOfMill(std::shared_ptr<GameObject> parent) override;
};

