#pragma once
#include "GameComponent.h"
class HealthComponent : public GameComponent
{
private:
	short health;
	float invincibilityTime;
	float timeSinceHealthReduction;

	// Testing
	float autoDamageTimer = 0.0f;
	const float autoDamageInterval = 10.0f;

public:
	HealthComponent(short playerHealth, float invincibilityTime);
	~HealthComponent() = default;
	//decrease health
	void decreaseHealth();
	//notify death
	void notifyDeath();
	void drawUI(int screenWidth, int screenHeight) const;
	virtual void update(float deltaTime) override;
};

