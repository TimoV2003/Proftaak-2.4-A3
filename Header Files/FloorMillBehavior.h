#pragma once
#include "IEndOfMillBehavior.h"

class FloorMillBehavior : public IEndOfMillBehavior
{
	bool taggedEnd = false;
public:
	FloorMillBehavior() = default;
	~FloorMillBehavior() = default;

	void ReachedEndOfMill(std::shared_ptr<GameObject> parent) override;
};

