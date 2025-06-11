#pragma once
#include "CollisionComponent.h"
#include <functional>
#include <memory>

class EnemyComponent : public CollisionComponent {
private:
	std::shared_ptr<GameObject> player = nullptr;
	std::function<void()> onPlayerCollision;

public:
	EnemyComponent(std::shared_ptr<GameObject> player, std::function<void()> onPlayerCollision) : player(player), onPlayerCollision(onPlayerCollision) {};
	~EnemyComponent() = default;
	virtual void update(float deltaTime) override;
};
