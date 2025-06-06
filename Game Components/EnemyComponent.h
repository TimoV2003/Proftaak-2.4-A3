#pragma once
#include "CollisionComponent.h"
#include "I_Observer.h"

class EnemyComponent : public CollisionComponent {
private:
	std::shared_ptr<GameObject> player = nullptr;
	std::vector<ICollisionObserver*> observers;
	void notifyEnemyObservers();

public:
	EnemyComponent(std::shared_ptr<GameObject> player) : player(player) {};
	~EnemyComponent() = default;
	virtual void update(float deltaTime) override;
	void addObserver(ICollisionObserver* observer);
};
