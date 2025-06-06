#pragma once
#include "GameComponent.h"


class EnemyComponent : public GameComponent
{
public:
	EnemyComponent() = default;
	~EnemyComponent() = default;
	virtual void update(float deltaTime) override;
	bool collides(GameObject* other);
};
