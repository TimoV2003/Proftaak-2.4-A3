#pragma once
#include "IEndOfMillBehavior.h"

class FloorMillBehavior : public IEndOfMillBehavior
{
public:
	FloorMillBehavior() = default;
	~FloorMillBehavior() = default;

	void ReachedEndOfMill(std::shared_ptr<GameObject> parent) override;
};

