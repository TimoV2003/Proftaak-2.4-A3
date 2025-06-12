#include "TreadmillComponent.h"
#include <iostream>
 
void TreadmillComponent::update(float deltaTime) {
	static float PauseEndCheckTime = 0;

	if (auto weakParent = getParent()) {
		weakParent->position.z += (speed * deltaTime);

	if (PauseEndCheckTime >= maxEndCheckPausedTime) {
		PauseEndCheckTime = 0;
		EndCheckPaused = false;
	}

	if (EndCheckPaused) {
		PauseEndCheckTime += deltaTime;
		return;
	}

	if (weakParent->position.z > deletionDistance) {
		EndCheckPaused = true;
		std::cout << "Enemy has reached the end of the mill!" << std::endl;
		endOfMillBehavior->ReachedEndOfMill(weakParent);
	}
}
}