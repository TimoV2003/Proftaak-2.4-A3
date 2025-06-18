#include "DistanceScoreComponent.h"
#include "ScoreStrategy.h"

void DistanceScoreComponent::update(const float& deltaTime) {
	//TODO make distance score scale with the speed variable. currently its only based on time
	this->scoreHolder->addScore(deltaTime);
}
