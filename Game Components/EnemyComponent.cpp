#include "EnemyComponent.h"  
#include "GameObject.h"
#include "GameComponent.h"
#include <glm/glm.hpp>

void EnemyComponent::update(float deltaTime) {
    if (this->collides(this->player)) {
        notifyEnemyObservers();
    }
}

void EnemyComponent::addObserver(ICollisionObserver* observer) {
    this->observers.push_back(observer);
}

void EnemyComponent::notifyEnemyObservers() {
    for (ICollisionObserver* observer : this->observers) {
        observer->onCollision();
    }
}