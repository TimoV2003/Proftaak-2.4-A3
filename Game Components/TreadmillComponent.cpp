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
		endOfMillBehavior->ReachedEndOfMill(weakParent);
	}
}
}