#pragma once
#include "CollisionComponent.h"
#include "I_Observer.h"

class EnemyComponent : public CollisionComponent {
private:
	std::shared_ptr<GameObject> player = nullptr;
	std::vector<IPlayerCollisionObserver*> observers;
	void notifyEnemyObservers();

public:
	EnemyComponent(std::shared_ptr<GameObject> player) : player(player) {};
	~EnemyComponent() = default;
	virtual void update(float deltaTime) override;
	void addCollisionObserver(IPlayerCollisionObserver* observer);
};
