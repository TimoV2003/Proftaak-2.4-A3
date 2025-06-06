#include "CollisionComponent.h"
#include "GameObject.h"
#include <glm/glm.hpp>


bool CollisionComponent::collides(std::shared_ptr<GameObject> other) {
	if (auto p = this->getParent()) {
		// hardcoded radius for collision detection, needs to be replaced with actual radii from GameObjects
		return glm::distance(p->position, other->position) < 4;
	}
	return false;
}