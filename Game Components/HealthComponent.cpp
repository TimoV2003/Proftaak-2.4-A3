#include "HealthComponent.h"
#include <iostream>
#include "GameObject.h"
#include "GameService.h"

HealthComponent::HealthComponent(short playerHealth, float invincibilityTime){
	this->health = playerHealth;
	this->invincibilityTime = invincibilityTime;
	this->timeSinceHealthReduction = 0.0f;
}

void HealthComponent::update(const float& deltaTime) {
	if (this->timeSinceHealthReduction < this->invincibilityTime) {
		this->timeSinceHealthReduction += deltaTime;
	}
}

void HealthComponent::decreaseHealth() {
	if (!(this->timeSinceHealthReduction > this->invincibilityTime)) {
		return;
	}
	this->timeSinceHealthReduction = 0.0f;

	std::cout << "decreaseHealth called" << std::endl;

	this->health -= 1;
	if (this->health <= 0) {
		notifyDeath();
	}
}

void HealthComponent::notifyDeath() {
	if (auto p = getParent()) {
		if (p->game) {
			p->game->gameOver = true;
		}
	}

	//TODO notify something that health is 0
}
