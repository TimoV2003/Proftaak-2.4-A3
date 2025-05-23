#include "TreadmillComponent.h"
 
void TreadmillComponent::update() {
	parent->position.z += 2;
	if (parent->position.z > -10) {
		endOfMillBehavior->ReachedEndOfMill();
	}

}