#include "TreadmillComponent.h"
#include <iostream>
 
void TreadmillComponent::update(const float& deltaTime) {
	if (auto weakParent = getParent()) {
		weakParent->position.z += this->speed * deltaTime;

	if (weakParent->position.z > deletionDistance) {
		endOfMillBehavior->ReachedEndOfMill(weakParent);
	}
}