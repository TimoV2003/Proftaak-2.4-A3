#pragma once
#include "GameComponent.h"
#include "I_Observer.h"

class EnemyComponent : public GameComponent
{
private:
	std::shared_ptr<GameObject> player = nullptr;
	std::vector<IObserver*> observers;
	void notifyEnemyObservers();

public:
	EnemyComponent(std::shared_ptr<GameObject> player) : player(player) {};
	~EnemyComponent() = default;
	virtual void update(float deltaTime) override;
	bool collides(std::shared_ptr<GameObject> other);
	void addObserver(IObserver* observer);
};
