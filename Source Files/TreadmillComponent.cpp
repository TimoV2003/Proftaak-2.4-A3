#include "TreadmillComponent.h"
#include <iostream>
 
void TreadmillComponent::update(float deltaTime) {
	static float updateEndCheckTime = 0;

	if (auto weakParent = getParent()) {
		weakParent->position.z += (speed * deltaTime);

	if (updateEndCheckTime >= maxEndCheckPausedTime) {
		updateEndCheckTime = 0;
		UpdatePaused = false;
	}

	if (UpdatePaused) {
		updateEndCheckTime += deltaTime;
		return;
	}

	if (weakParent->position.z > deletionDistance) {
		UpdatePaused = true;
		std::cout << "Enemy has reached the end of the mill!" << std::endl;
		endOfMillBehavior->ReachedEndOfMill(weakParent);
	}
}
}