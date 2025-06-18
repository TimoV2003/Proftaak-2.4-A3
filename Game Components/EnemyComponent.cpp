#include "EnemyComponent.h"  
#include "GameObject.h"
#include "GameComponent.h"
#include <glm/glm.hpp>

void EnemyComponent::update(const float& deltaTime) {
    if (this->collides(this->player)) {
		this->onPlayerCollision();
    }
}