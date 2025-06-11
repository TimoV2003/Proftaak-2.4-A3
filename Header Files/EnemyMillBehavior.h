#pragma once
#include "IEndOfMillBehavior.h"

class EnemyMillBehavior : public IEndOfMillBehavior
{
public:
	EnemyMillBehavior() = default;
	~EnemyMillBehavior() = default;

	void ReachedEndOfMill(std::shared_ptr<GameObject> parent) override;
};

