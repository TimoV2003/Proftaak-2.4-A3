#include "EnemyComponent.h"  
#include "GameObject.h"
#include "GameComponent.h"
#include <glm/glm.hpp>

void EnemyComponent::update(float deltaTime) {
    if (this->collides(this->player)) {
        notifyEnemyObservers();
    }
}

void EnemyComponent::addCollisionObserver(IPlayerCollisionObserver* observer) {
    this->observers.push_back(observer);
}

void EnemyComponent::notifyEnemyObservers() {
    for (IPlayerCollisionObserver* observer : this->observers) {
        observer->onPlayerCollision();
    }
}