#include "CollisionComponent.h"
#include "GameObject.h"
#include <glm/glm.hpp>


bool CollisionComponent::collides(std::shared_ptr<GameObject> other) {
	if (auto p = this->getParent()) {
		return glm::distance(p->position, other->position) < (p->getCollisionSize()+other->getCollisionSize());
	}
	return false;
}