#pragma once
#include "IEndOfMillBehavior.h"

class EntityMillBehavior : public IEndOfMillBehavior
{
public:
	EntityMillBehavior() = default;
	~EntityMillBehavior() = default;

	void ReachedEndOfMill(std::shared_ptr<GameObject> parent) override;
};

