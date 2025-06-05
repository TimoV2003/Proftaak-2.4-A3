#pragma once
#include "IEndOfMillBehavior.h"

class EnemyMillBehavior : public IEndOfMillBehavior
{

public:
	EnemyMillBehavior() = default;
	~EnemyMillBehavior() = default;

	void ReachedEndOfMill() override;
};

