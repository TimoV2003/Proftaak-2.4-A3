#include "TreadmillComponent.h"
#include <iostream>
 
void TreadmillComponent::update(float deltaTime) {
	if (auto weakParent = getParent()) {
		weakParent->position.z += (speed * deltaTime);

	if (weakParent->position.z > deletionDistance) {
		endOfMillBehavior->ReachedEndOfMill(weakParent);
	}
}
}