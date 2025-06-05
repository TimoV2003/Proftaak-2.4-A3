#pragma once
#include "IEndOfMillBehavior.h"

class EnemyMillBehavior : public IEndOfMillBehavior
{
	bool taggedEnd = false;
public:
	EnemyMillBehavior() = default;
	~EnemyMillBehavior() = default;

	void ReachedEndOfMill() override;
};

