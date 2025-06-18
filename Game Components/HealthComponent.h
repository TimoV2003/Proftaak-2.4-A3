#pragma once
#include "GameComponent.h"
class HealthComponent : public GameComponent {
private:
	short health;
	float invincibilityTime;
	float timeSinceHealthReduction;
public:
	HealthComponent(short playerHealth, float invincibilityTime);
	~HealthComponent() = default;
	//decrease health
	void decreaseHealth();
	//notify death
	void notifyDeath();
	virtual void update(const float& deltaTime) override;

#ifdef _DEBUG
	short getHealthDebug() { return health; }
#endif
};

