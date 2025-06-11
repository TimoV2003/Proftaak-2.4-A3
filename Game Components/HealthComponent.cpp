#include "HealthComponent.h"
#include <iostream>

HealthComponent::HealthComponent(short playerHealth){
	health = playerHealth;
}

void HealthComponent::decreaseHealth() {
	std::cout << "Health decreased called" << std::endl;
	/*health -= 1;
	if (health <= 0) {
		notifyDeath();
	}*/
}

void HealthComponent::notifyDeath() {
	//TODO notify something that health is 0
}
