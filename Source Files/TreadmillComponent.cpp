#include "TreadmillComponent.h"
 
void TreadmillComponent::update(float deltaTime) {

	if (auto weakParent = getParent()){
	weakParent->position.z += (2*deltaTime);
	if (weakParent->position.z > -10) {
		endOfMillBehavior->ReachedEndOfMill();
	}
}
}