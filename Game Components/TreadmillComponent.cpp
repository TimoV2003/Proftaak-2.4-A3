#include "TreadmillComponent.h"
#include <iostream>
#include <cmath>
#include "GameService.h"
#include "DistanceScoreComponent.h"
#include "ScoreStrategy.h"
 
void TreadmillComponent::update(float deltaTime) {
	if (auto weakParent = getParent()) {
		weakParent->position.z += (speed * deltaTime);

		if (weakParent->position.z > deletionDistance) {
			endOfMillBehavior->ReachedEndOfMill(weakParent);
		}
	}

	speed = updateMovementSpeed();
}

float TreadmillComponent::updateMovementSpeed() {
	auto player = GameService::getGameObject("blocky");
	auto scoreComponent = player ? player->getComponent<DistanceScoreComponent>() : nullptr;
	float points = scoreComponent->getScoreHolder()->getScore();
	return (initialSpeed + (100 * (1 - pow(2.718, -0.01 * points))));
}