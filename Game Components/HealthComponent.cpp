#include "HealthComponent.h"

HealthComponent::HealthComponent(short playerHealth){
	health = playerHealth;
}

void HealthComponent::decreaseHealth() {
	health -= 1;
	if (health <= 0) {
		notifyDeath();
	}
}

void HealthComponent::notifyDeath() {
	//TODO notify something that health is 0
}
