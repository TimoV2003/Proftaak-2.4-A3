#include "TreadmillComponent.h"
#include <iostream>
 
void TreadmillComponent::update(float deltaTime) {

	if (auto weakParent = getParent()){
	weakParent->position.z += (speed * deltaTime);
	if (weakParent->position.z > deletionDistance && !ReachedEnd) {
		ReachedEnd = true;
		std::cout << "Enemy has reached the end of the mill!" << std::endl;

		endOfMillBehavior->ReachedEndOfMill(weakParent);
	}
}
}