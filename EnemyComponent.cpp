#include "EnemyComponent.h"  
#include "GameObject.h"
#include "GameComponent.h"
#include <glm/glm.hpp>

void EnemyComponent::update(float deltaTime) {

}

bool EnemyComponent::collides(GameObject* other) {
    if (auto p = this->getParent()) {
        return glm::distance(p->position, other->position) < 4;
    }
    return false;
}
