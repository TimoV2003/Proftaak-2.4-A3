#include "TreadmillComponent.h"
#include <iostream>
 


void TreadmillComponent::update(const float& deltaTime) {
	static float PauseEndCheckTime = 0;
	static bool EndCheckPaused = false;

	if (auto weakParent = getParent()) {
		weakParent->position.z += this->speed * deltaTime;

		if (PauseEndCheckTime >= this->maxEndCheckPausedTime) {
			PauseEndCheckTime = 0;
			EndCheckPaused = false;
		}

		if (EndCheckPaused) {
			PauseEndCheckTime += deltaTime;
			return;
		}

		if (weakParent->position.z > this->deletionDistance) {
			EndCheckPaused = true;
			this->endOfMillBehavior->ReachedEndOfMill(weakParent);
		}
	}
}