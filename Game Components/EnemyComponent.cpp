#include "EnemyComponent.h"  
#include "GameObject.h"
#include "GameComponent.h"
#include <glm/glm.hpp>

void EnemyComponent::update(float deltaTime) {
    if (collides(this->player)) {
        notifyEnemyObservers();
    }
}

bool EnemyComponent::collides(std::shared_ptr<GameObject> other) {
    if (auto p = this->getParent()) {
        return glm::distance(p->position, other->position) < 4;
    }
    return false;
}

void EnemyComponent::addObserver(ICollisionObserver* observer) {
    this->observers.push_back(observer);
}

void EnemyComponent::notifyEnemyObservers() {
    for (ICollisionObserver* observer : this->observers) {
        observer->onCollision();
    }
}