#pragma once
#include "IEndOfMillBehavior.h"

class EnemyMillBehavior : public IEndOfMillBehavior
{
	bool taggedEnd = false;
public:
	EnemyMillBehavior() = default;
	~EnemyMillBehavior() = default;

	void ReachedEndOfMill(std::shared_ptr<GameObject> parent) override;
};

