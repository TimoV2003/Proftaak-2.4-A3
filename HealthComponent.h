#pragma once
#include "GameComponent.h"
class HealthComponent : public GameComponent
{
private:
	short health;
public:
	HealthComponent(short playerHealth);
	~HealthComponent() = default;
	//decrease health
	void decreaseHealth();
	//notify death
	void notifyDeath();

};

