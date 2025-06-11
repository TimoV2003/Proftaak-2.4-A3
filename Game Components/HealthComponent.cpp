#include "HealthComponent.h"
#include "GameObject.h"
#include "GameService.h"

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
	if (auto p = getParent()) {
		if (p->game) {
			p->game->gameOver = true;
		}
	}

	//TODO notify something that health is 0
}
