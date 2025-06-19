#include "CollisionComponent.h"
#include "GameObject.h"
#include <cmath>


bool CollisionComponent::collides(std::shared_ptr<GameObject> other) const {
	if (auto p = this->getParent()) {
		auto x = p->position.x - other->position.x;
		auto z = p->position.z - other->position.z;
		return sqrt((x * x) + (z * z)) < (p->getCollisionSize() + other->getCollisionSize());
	}
	return false;
}